/*  EQEMu:  Everquest Server Emulator
	Copyright (C) 2001-2005  EQEMu Development Team (http://eqemulator.net)

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
#include "../common/eq_packet_structs.h"
#include "masterentity.h"
#include "titles.h"
#include "../common/MiscFunctions.h"

TitleManager::TitleManager() {
}

bool TitleManager::LoadTitles()
{
	Titles.clear();

	TitleEntry Title;
	
	char errbuf[MYSQL_ERRMSG_SIZE];
	char *query = NULL;
	MYSQL_RES *result;
	MYSQL_ROW row;

	if (!database.RunQuery(query, MakeAnyLenString(&query, 
		"SELECT `id`, `skill_id`, `min_skill_value`, `max_skill_value`, `min_aa_points`, `max_aa_points`, `class`, `gender`, "
		"`char_id`, `status`, `item_id`, `prefix`, `suffix` from titles"), errbuf, &result))
	{
		LogFile->write(EQEMuLog::Error, "Unable to load titles: %s : %s", query, errbuf);
		safe_delete_array(query);
		return(false);
	}

	safe_delete_array(query);
	
	while ((row = mysql_fetch_row(result))) {
		Title.TitleID = atoi(row[0]);
		Title.SkillID = (SkillType) atoi(row[1]);
		Title.MinSkillValue = atoi(row[2]);
		Title.MaxSkillValue = atoi(row[3]);
		Title.MinAAPoints = atoi(row[4]);
		Title.MaxAAPoints = atoi(row[5]);
		Title.Class = atoi(row[6]);
		Title.Gender = atoi(row[7]);
		Title.CharID = atoi(row[8]);
		Title.Status = atoi(row[9]);
		Title.ItemID = atoi(row[10]);
		Title.Prefix = row[11];
		Title.Suffix = row[12];
		Titles.push_back(Title);
	}
	mysql_free_result(result);
	
	return(true);
}

EQApplicationPacket *TitleManager::MakeTitlesPacket(Client *c)
{
	vector<TitleEntry>::iterator Iterator;

	vector<TitleEntry> AvailableTitles;

	uint32 Length = 4;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if(!IsClientEligibleForTitle(c, Iterator))
		{
			++Iterator;
			continue;
		}

		AvailableTitles.push_back((*Iterator));

		Length += Iterator->Prefix.length() + Iterator->Suffix.length() + 6;

		++Iterator;

	}

	EQApplicationPacket *outapp = new EQApplicationPacket(OP_SendTitleList, Length);

	char *Buffer = (char *)outapp->pBuffer;

	VARSTRUCT_ENCODE_TYPE(uint32, Buffer, AvailableTitles.size());
	
	Iterator = AvailableTitles.begin();

	while(Iterator != AvailableTitles.end())
	{
		VARSTRUCT_ENCODE_TYPE(uint32, Buffer, Iterator->TitleID);

		VARSTRUCT_ENCODE_STRING(Buffer, Iterator->Prefix.c_str());

		VARSTRUCT_ENCODE_STRING(Buffer, Iterator->Suffix.c_str());

		++Iterator;
	}
	return(outapp);
}

int TitleManager::NumberOfAvailableTitles(Client *c)
{
	int Count = 0;

	vector<TitleEntry>::iterator Iterator;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if(IsClientEligibleForTitle(c, Iterator))
			++Count;

		++Iterator;
	}

	return Count;
}

string TitleManager::GetPrefix(int TitleID)
{
	vector<TitleEntry>::iterator Iterator;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if((*Iterator).TitleID == TitleID)
			return (*Iterator).Prefix;

		++Iterator;
	}

	return "";
}

string TitleManager::GetSuffix(int TitleID)
{
	vector<TitleEntry>::iterator Iterator;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if((*Iterator).TitleID == TitleID)
			return (*Iterator).Suffix;

		Iterator++;
	}

	return "";
}

bool TitleManager::IsClientEligibleForTitle(Client *c, vector<TitleEntry>::iterator Title)
{
		if((Title->CharID >= 0) && (c->CharacterID() != static_cast<int32>(Title->CharID)))
			return false;

		if((Title->Status >= 0) && (c->Admin() < Title->Status))
			return false;

		if((Title->Gender >= 0) && (c->GetBaseGender() != Title->Gender))
			return false;

		if((Title->Class >= 0) && (c->GetBaseClass() != Title->Class))
			return false;

		if((Title->MinAAPoints >= 0) && (c->GetAAPointsSpent() < static_cast<uint32>(Title->MinAAPoints)))
			return false;

		if((Title->MaxAAPoints >= 0) && (c->GetAAPointsSpent() > static_cast<uint32>(Title->MaxAAPoints)))
			return false;

		if(Title->SkillID >= 0)
		{
			if((Title->MinSkillValue >= 0)
			   && (c->GetRawSkill(static_cast<SkillType>(Title->SkillID)) < static_cast<uint32>(Title->MinSkillValue)))
				return false;

			if((Title->MaxSkillValue >= 0)
			   && (c->GetRawSkill(static_cast<SkillType>(Title->SkillID)) > static_cast<uint32>(Title->MaxSkillValue)))
				return false;

		}

		if((Title->ItemID >= 1) && (c->GetInv().HasItem(Title->ItemID, 0, 0xFF) == SLOT_INVALID))
			return false;

		return true;
}

bool TitleManager::IsNewAATitleAvailable(int AAPoints, int Class)
{
	vector<TitleEntry>::iterator Iterator;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if((((*Iterator).Class == -1) || ((*Iterator).Class == Class)) && ((*Iterator).MinAAPoints == AAPoints))
			return true;

		++Iterator;
	}

	return false;
}

bool TitleManager::IsNewTradeSkillTitleAvailable(int SkillID, int SkillValue)
{
	vector<TitleEntry>::iterator Iterator;

	Iterator = Titles.begin();

	while(Iterator != Titles.end())
	{
		if(((*Iterator).SkillID == SkillID) && ((*Iterator).MinSkillValue == SkillValue))
			return true;

		++Iterator;
	}

	return false;
}
