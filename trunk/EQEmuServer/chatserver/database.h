/*
	EQEMu:  Everquest Server Emulator

	Copyright (C) 2001-2008 EQEMu Development Team (http://eqemulator.net)

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

#ifndef CHATSERVER_DATABASE_H
#define CHATSERVER_DATABASE_H

#define AUTHENTICATION_TIMEOUT	60
#define INVALID_ID				0xFFFFFFFF

#include "../common/debug.h"
#include "../common/types.h"
#include "../common/dbcore.h"
#include "../common/linked_list.h"
#include "clientlist.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

//atoi is not int32 or uint32 safe!!!!
#define atoul(str) strtoul(str, NULL, 10)

class Database : public DBcore {
public:
	Database();
	Database(const char* host, const char* user, const char* passwd, const char* database,int32 port);
	bool Connect(const char* host, const char* user, const char* passwd, const char* database,int32 port);
	~Database();

	int FindAccount(const char *CharacterName, Client *c);
	int FindCharacter(const char *CharacterName);
	bool VerifyMailKey(string CharacterName, int IPAddress, string MailKey);
	bool GetVariable(const char* varname, char* varvalue, int16 varvalue_len);
	bool LoadChatChannels();
	void GetAccountStatus(Client *c);
	void SetChannelPassword(string ChannelName, string Password);
	void SetChannelOwner(string ChannelName, string Owner);
	
	

protected:
	void	HandleMysqlError(int32 errnum);
private:
	void DBInitVars();
	
};

#endif
