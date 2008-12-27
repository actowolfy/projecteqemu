#include "debug.h"

#include <iostream>
using namespace std;
#include <time.h>
#include <string.h>
#ifdef WIN32
	#include <process.h>

	#define snprintf	_snprintf
#if (_MSC_VER < 1500)
	#define vsnprintf	_vsnprintf
#endif
	#define strncasecmp	_strnicmp
	#define strcasecmp  _stricmp
#else
	#include <sys/types.h>
	#include <unistd.h>
	#include <stdarg.h>
#endif
#include "../common/MiscFunctions.h"

static volatile bool logFileValid = false;
static EQEMuLog realLogFile;
EQEMuLog *LogFile = &realLogFile;

static const char* FileNames[EQEMuLog::MaxLogID] = { "logs/eqemu", "logs/eqemu", "logs/eqemu_error", "logs/eqemu_debug", "logs/eqemu_quest", "logs/eqemu_commands" };
static const char* LogNames[EQEMuLog::MaxLogID] = { "Status", "Normal", "Error", "Debug", "Quest", "Command" };

EQEMuLog::EQEMuLog() {
//	MOpen = new Mutex;
//	MLog = new Mutex*[MaxLogID];
//	fp = new FILE*[MaxLogID];
//	pLogStatus = new int8[MaxLogID];
	for (int i=0; i<MaxLogID; i++) {
		fp[i] = 0;
//		MLog[i] = new Mutex;
#if EQDEBUG >= 2
		pLogStatus[i] = 1 | 2;
#else
		pLogStatus[i] = 0;
#endif
		logCallbackFmt[i] = NULL;
		logCallbackBuf[i] = NULL;
		logCallbackPva[i] = NULL;
	}
// TODO: Make this read from an ini or something, everyone has different opinions on what it should be
#if EQDEBUG < 2
	pLogStatus[Status] = 2;
	pLogStatus[Error] = 2;
	pLogStatus[Quest] = 2;
	pLogStatus[Commands] = 1;
#endif
	logFileValid = true;
}

EQEMuLog::~EQEMuLog() {
	logFileValid = false;
	for (int i=0; i<MaxLogID; i++) {
		LockMutex lock(&MLog[i]);	//to prevent termination race
		if (fp[i])
			fclose(fp[i]);
	}
//	safe_delete_array(fp);
//	safe_delete_array(MLog);
//	safe_delete_array(pLogStatus);
//	safe_delete(MOpen);
}

bool EQEMuLog::open(LogIDs id) {
	if (!logFileValid) {
		return false;
    }
	if (id >= MaxLogID) {
		return false;
    }
	LockMutex lock(&MOpen);
	if (pLogStatus[id] & 4) {
		return false;
    }
    if (fp[id]) {
        //cerr<<"Warning: LogFile already open"<<endl;
        return true;
    }

	char exename[200] = "";
#if defined(WORLD)
	snprintf(exename, sizeof(exename), "_world");
#elif defined(ZONE)
	snprintf(exename, sizeof(exename), "_zone");
#elif defined(LAUNCHER)
	snprintf(exename, sizeof(exename), "_launch");
#elif defined(MAIL)
	snprintf(exename, sizeof(exename), "_mail");
#endif
	char filename[200];
#ifndef NO_PIDLOG
	snprintf(filename, sizeof(filename), "%s%s_%04i.log", FileNames[id], exename, getpid());
#else
	snprintf(filename, sizeof(filename), "%s%s.log", FileNames[id], exename);
#endif
    fp[id] = fopen(filename, "a");
    if (!fp[id]) {
		cerr << "Failed to open log file: " << filename << endl;
		pLogStatus[id] |= 4; // set file state to error
        return false;
    }
    fputs("---------------------------------------------\n",fp[id]);
    write(id, "Starting Log: %s", filename);
    return true;
}

bool EQEMuLog::write(LogIDs id, const char *fmt, ...) {
	if (!logFileValid) {
		return false;
    }
	if (id >= MaxLogID) {
		return false;
    }
	bool dofile = false;
	if (pLogStatus[id] & 1) {
		dofile = open(id);
	}
	if (!(dofile || pLogStatus[id] & 2))
		return false;
	LockMutex lock(&MLog[id]);
	if (!logFileValid)
		return false;	//check again for threading race reasons (to avoid two mutexes)

    time_t aclock;
    struct tm *newtime;
    
    time( &aclock );                 /* Get time in seconds */
    newtime = localtime( &aclock );  /* Convert time to struct */

    if (dofile)
#ifndef NO_PIDLOG
		fprintf(fp[id], "[%02d.%02d. - %02d:%02d:%02d] ", newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
#else
		fprintf(fp[id], "%04i [%02d.%02d. - %02d:%02d:%02d] ", getpid(), newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
#endif

	va_list argptr;
	va_start(argptr, fmt);
    if (dofile)
		vfprintf( fp[id], fmt, argptr );
	if(logCallbackFmt[id]) {
		msgCallbackFmt p = logCallbackFmt[id];
		p(id, fmt, argptr );
	}
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8) {
			fprintf(stderr, "[%s] ", LogNames[id]);
			vfprintf( stderr, fmt, argptr );
		}
		else {
			fprintf(stdout, "[%s] ", LogNames[id]);
			vfprintf( stdout, fmt, argptr );
		}
	}
	va_end(argptr);
    if (dofile)
		fprintf(fp[id], "\n");
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8) {
			fprintf(stderr, "\n");
			fflush(stderr);
		} else {
			fprintf(stdout, "\n");
			fflush(stdout);
		}
	}
    if(dofile)
      fflush(fp[id]);
    return true;
}

//write with Prefix and a VA_list
bool EQEMuLog::writePVA(LogIDs id, const char *prefix, const char *fmt, va_list argptr) {
	if (!logFileValid) {
		return false;
    }
	if (id >= MaxLogID) {
		return false;
    }
	bool dofile = false;
	if (pLogStatus[id] & 1) {
		dofile = open(id);
	}
	if (!(dofile || pLogStatus[id] & 2)) {
		return false;
	}
	LockMutex lock(&MLog[id]);
	if (!logFileValid)
		return false;	//check again for threading race reasons (to avoid two mutexes)

    time_t aclock;
    struct tm *newtime;
    
    time( &aclock );                 /* Get time in seconds */
    newtime = localtime( &aclock );  /* Convert time to struct */

    if (dofile) {
#ifndef NO_PIDLOG
		fprintf(fp[id], "[%02d.%02d. - %02d:%02d:%02d] %s", newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec, prefix);
#else
		fprintf(fp[id], "%04i [%02d.%02d. - %02d:%02d:%02d] %s", getpid(), newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec, prefix);
#endif
		vfprintf( fp[id], fmt, argptr );
    }
	if(logCallbackPva[id]) {
		msgCallbackPva p = logCallbackPva[id];
		p(id, prefix, fmt, argptr );
	}
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8) {
			fprintf(stderr, "[%s] %s", LogNames[id], prefix);
			vfprintf( stderr, fmt, argptr );
		}
		else {
			fprintf(stdout, "[%s] %s", LogNames[id], prefix);
			vfprintf( stdout, fmt, argptr );
		}
	}
	va_end(argptr);
    if (dofile)
		fprintf(fp[id], "\n");
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8)
			fprintf(stderr, "\n");
		else
			fprintf(stdout, "\n");
	}
    if(dofile)
      fflush(fp[id]);
    return true;
}

bool EQEMuLog::writebuf(LogIDs id, const char *buf, int8 size, int32 count) {
	if (!logFileValid) {
		return false;
    }
	if (id >= MaxLogID) {
		return false;
    }
	bool dofile = false;
	if (pLogStatus[id] & 1) {
		dofile = open(id);
	}
	if (!(dofile || pLogStatus[id] & 2))
		return false;
	LockMutex lock(&MLog[id]);
	if (!logFileValid)
		return false;	//check again for threading race reasons (to avoid two mutexes)

    time_t aclock;
    struct tm *newtime;
    
    time( &aclock );                 /* Get time in seconds */
    newtime = localtime( &aclock );  /* Convert time to struct */

    if (dofile)
#ifndef NO_PIDLOG
		fprintf(fp[id], "[%02d.%02d. - %02d:%02d:%02d] ", newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
#else
		fprintf(fp[id], "%04i [%02d.%02d. - %02d:%02d:%02d] ", getpid(), newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
#endif

	if (dofile) {
		fwrite(buf, size, count, fp[id]);
		fprintf(fp[id], "\n");
	}
	if(logCallbackBuf[id]) {
		msgCallbackBuf p = logCallbackBuf[id];
		p(id, buf, size, count);
	}
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8) {
			fprintf(stderr, "[%s] ", LogNames[id]);
			fwrite(buf, size, count, stderr);
			fprintf(stderr, "\n");
		} else {
			fprintf(stdout, "[%s] ", LogNames[id]);
			fwrite(buf, size, count, stdout);
			fprintf(stdout, "\n");
		}
	}
    if(dofile)
      fflush(fp[id]);
    return true;
}

bool EQEMuLog::writeNTS(LogIDs id, bool dofile, const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	if (dofile)
		vfprintf( fp[id], fmt, argptr );
    if (pLogStatus[id] & 2) {
		if (pLogStatus[id] & 8)
			vfprintf( stderr, fmt, argptr );
		else
			vfprintf( stdout, fmt, argptr );
	}
	va_end(argptr);
    return true;
};

bool EQEMuLog::Dump(LogIDs id, int8* data, int32 size, int32 cols, int32 skip) {
	if (!logFileValid) {
#if EQDEBUG >= 10
    cerr << "Error: Dump() from null pointer"<<endl;
#endif
		return false;
    }
	if (size == 0)
		return true;
	if (!LogFile)
		return false;
	if (id >= MaxLogID)
		return false;
	bool dofile = false;
	if (pLogStatus[id] & 1) {
		dofile = open(id);
	}
	if (!(dofile || pLogStatus[id] & 2))
		return false;
	LockMutex lock(&MLog[id]);
	if (!logFileValid)
		return false;	//check again for threading race reasons (to avoid two mutexes)
	
	write(id, "Dumping Packet: %i", size);
	// Output as HEX
	int j = 0; char* ascii = new char[cols+1]; memset(ascii, 0, cols+1);
	int32 i;
    for(i=skip; i<size; i++) {
		if ((i-skip)%cols==0) {
			if (i != skip)
				writeNTS(id, dofile, " | %s\n", ascii);
			writeNTS(id, dofile, "%4i: ", i-skip);
			memset(ascii, 0, cols+1);
			j = 0;
		}
		else if ((i-skip)%(cols/2) == 0) {
			writeNTS(id, dofile, "- ");
		}
		writeNTS(id, dofile, "%02X ", (unsigned char)data[i]);

		if (data[i] >= 32 && data[i] < 127)
			ascii[j++] = data[i];
		else
			ascii[j++] = '.';
    }
	int32 k = ((i-skip)-1)%cols;
	if (k < 8)
		writeNTS(id, dofile, "  ");
	for (int32 h = k+1; h < cols; h++) {
		writeNTS(id, dofile, "   ");
	}
	writeNTS(id, dofile, " | %s\n", ascii);
	if (dofile)
		fflush(fp[id]);
	safe_delete_array(ascii);
	return true;
}
	
void EQEMuLog::SetCallback(LogIDs id, msgCallbackFmt proc) {
	if (!logFileValid)
		return;
	if (id >= MaxLogID) {
		return;
    }
    logCallbackFmt[id] = proc;
}

void EQEMuLog::SetCallback(LogIDs id, msgCallbackBuf proc) {
	if (!logFileValid)
		return;
	if (id >= MaxLogID) {
		return;
    }
    logCallbackBuf[id] = proc;
}

void EQEMuLog::SetCallback(LogIDs id, msgCallbackPva proc) {
	if (!logFileValid)
		return;
	if (id >= MaxLogID) {
		return;
    }
    logCallbackPva[id] = proc;
}

void EQEMuLog::SetAllCallbacks(msgCallbackFmt proc) {
	if (!logFileValid)
		return;
	int r;
	for(r = Status; r < MaxLogID; r++) {
		SetCallback((LogIDs)r, proc);
	}
}

void EQEMuLog::SetAllCallbacks(msgCallbackBuf proc) {
	if (!logFileValid)
		return;
	int r;
	for(r = Status; r < MaxLogID; r++) {
		SetCallback((LogIDs)r, proc);
	}
}

void EQEMuLog::SetAllCallbacks(msgCallbackPva proc) {
	if (!logFileValid)
		return;
	int r;
	for(r = Status; r < MaxLogID; r++) {
		SetCallback((LogIDs)r, proc);
	}
}



