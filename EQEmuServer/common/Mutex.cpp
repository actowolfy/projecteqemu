/*  EQEMu:  Everquest Server Emulator
    Copyright (C) 2001-2002  EQEMu Development Team (http://eqemu.org)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "../common/debug.h"
#include "../common/Mutex.h"

#include <iostream>
using namespace std;

#define DEBUG_MUTEX_CLASS 0
#if DEBUG_MUTEX_CLASS >= 1
	
#endif

#ifdef _WINDOWS
bool IsTryLockSupported();
bool TrylockSupported = IsTryLockSupported();

bool IsTryLockSupported() {
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) {
#if DEBUG_MUTEX_CLASS >= 1
			cout << "Mutex::trylock() NOT supported" << endl;
#endif
			return false;
		}
	}

	// Tests for Windows NT product family.
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion >= 4) {
#if DEBUG_MUTEX_CLASS >= 1
			cout << "Mutex::trylock() SUPPORTED" << endl;
#endif
		return true;
	}
	else {
#if DEBUG_MUTEX_CLASS >= 1
			cout << "Mutex::trylock() NOT supported" << endl;
#endif
		return false;
	}
}
#endif

Mutex::Mutex() {
#if DEBUG_MUTEX_CLASS >= 7
	cout << "Constructing Mutex" << endl;
#endif
#ifdef _WINDOWS
	InitializeCriticalSection(&CSMutex);
#else
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
#if defined(__CYGWIN__) || defined(__APPLE__)
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#else
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
	pthread_mutex_init(&CSMutex, &attr);
	pthread_mutexattr_destroy(&attr);
#endif
}

Mutex::~Mutex() {
#if DEBUG_MUTEX_CLASS >= 7
	cout << "Deconstructing Mutex" << endl;
#endif
#ifdef _WINDOWS
	DeleteCriticalSection(&CSMutex);
#else
//	pthread_mutex_destroy(&CSMutex);
#endif
}

void Mutex::lock() {
	_CP(Mutex_lock);
#if DEBUG_MUTEX_CLASS >= 9
	cout << "Locking Mutex" << endl;
#endif
#if DEBUG_MUTEX_CLASS >= 5
	if (!trylock()) {
		cout << "Locking Mutex: Having to wait" << endl;
		#ifdef _WINDOWS
			EnterCriticalSection(&CSMutex);
		#else
			pthread_mutex_lock(&CSMutex);
		#endif
	}
#else
	#ifdef _WINDOWS
		EnterCriticalSection(&CSMutex);
	#else
		pthread_mutex_lock(&CSMutex);
	#endif
#endif
}

bool Mutex::trylock() {
#if DEBUG_MUTEX_CLASS >= 9
	cout << "TryLocking Mutex" << endl;
#endif
#ifdef _WINDOWS
	#if(_WIN32_WINNT >= 0x0400)
		if (TrylockSupported)
			return TryEnterCriticalSection(&CSMutex);
		else {
			EnterCriticalSection(&CSMutex);
			return true;
		}
	#else
		EnterCriticalSection(&CSMutex);
		return true;
	#endif
#else
	return (pthread_mutex_trylock(&CSMutex) == 0);
#endif
}

void Mutex::unlock() {
#if DEBUG_MUTEX_CLASS >= 9
	cout << "Unlocking Mutex" << endl;
#endif
#ifdef _WINDOWS
	LeaveCriticalSection(&CSMutex);
#else
	pthread_mutex_unlock(&CSMutex);
#endif
}


LockMutex::LockMutex(Mutex* in_mut, bool iLock) {
	mut = in_mut;
	locked = iLock;
	if (locked) {
		mut->lock();
	}
}

LockMutex::~LockMutex() {
	if (locked) {
		mut->unlock();
	}
}

void LockMutex::unlock() {
	if (locked)
		mut->unlock();
	locked = false;
}

void LockMutex::lock() {
	if (!locked)
		mut->lock();
	locked = true;
}


MRMutex::MRMutex() {
	rl = 0;
	wr = 0;
	rl = 0;
}

MRMutex::~MRMutex() {
#ifdef _EQDEBUG
	if (wl || rl) {
		cout << "MRMutex::~MRMutex: poor cleanup detected: rl=" << rl << ", wl=" << wl << endl;
	}
#endif
}

void MRMutex::ReadLock() {
	while (!TryReadLock()) {
		Sleep(1);
	}
}

bool MRMutex::TryReadLock() {
	MCounters.lock();
	if (!wr && !wl) {
		rl++;
		MCounters.unlock();
		return true;
	}
	else {
		MCounters.unlock();
		return false;
	}
}

void MRMutex::UnReadLock() {
	MCounters.lock();
	rl--;
#ifdef _EQDEBUG
	if (rl < 0) {
		ThrowError("rl < 0 in MRMutex::UnReadLock()");
	}
#endif
	MCounters.unlock();
}

void MRMutex::WriteLock() {
	MCounters.lock();
	if (!rl && !wl) {
		wl++;
		MCounters.unlock();
		return;
	}
	else {
		wr++;
		MCounters.unlock();
		while (1) {
			Sleep(1);
			MCounters.lock();
			if (!rl && !wl) {
				wr--;
				MCounters.unlock();
				return;
			}
			MCounters.lock();
		}
	}
}

bool MRMutex::TryWriteLock() {
	MCounters.lock();
	if (!rl && !wl) {
		wl++;
		MCounters.unlock();
		return true;
	}
	else {
		MCounters.unlock();
		return false;
	}
}

void MRMutex::UnWriteLock() {
	MCounters.lock();
	wl--;
#ifdef _EQDEBUG
	if (wl < 0) {
		ThrowError("wl < 0 in MRMutex::UnWriteLock()");
	}
#endif
	MCounters.unlock();
}

int32 MRMutex::ReadLockCount() {
	MCounters.lock();
	int32 ret = rl;
	MCounters.unlock();
	return ret;
}

int32 MRMutex::WriteLockCount() {
	MCounters.lock();
	int32 ret = wl;
	MCounters.unlock();
	return ret;
}

