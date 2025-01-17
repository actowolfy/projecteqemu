/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of tmp. Do not edit this file, edit tmp instead.
 *
 *		ANY CHANGES MADE HERE WILL BE LOST!
 *
 */


/*  EQEMu:  Everquest Server Emulator
	Copyright (C) 2001-2004  EQEMu Development Team (http://eqemulator.net)

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

#include "features.h"
#ifdef EMBPERL_XS_CLASSES
#include "../common/debug.h"
#include "embperl.h"

#include "groups.h"

#ifdef THIS	 /* this macro seems to leak out on some systems */
#undef THIS		
#endif


XS(XS_Group_DisbandGroup); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_DisbandGroup)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::DisbandGroup(THIS)");
	{
		Group *		THIS;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->DisbandGroup();
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_IsGroupMember); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_IsGroupMember)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::IsGroupMember(THIS, client)");
	{
		Group *		THIS;
		bool		RETVAL;
		Mob*		client;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			client = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "client is not of type Mob");
		if(client == NULL)
			Perl_croak(aTHX_ "client is NULL, avoiding crash.");

		RETVAL = THIS->IsGroupMember(client);
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_Group_CastGroupSpell); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_CastGroupSpell)
{
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: Group::CastGroupSpell(THIS, caster, spellid)");
	{
		Group *		THIS;
		Mob*		caster;
		uint16		spellid = (uint16)SvUV(ST(2));

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			caster = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "caster is not of type Mob");
		if(caster == NULL)
			Perl_croak(aTHX_ "caster is NULL, avoiding crash.");

		THIS->CastGroupSpell(caster, spellid);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_SplitExp); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_SplitExp)
{
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: Group::SplitExp(THIS, exp, other)");
	{
		Group *		THIS;
		uint32		exp = (uint32)SvUV(ST(1));
		Mob*		other;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(2), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(2)));
			other = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "other is not of type Mob");
		if(other == NULL)
			Perl_croak(aTHX_ "other is NULL, avoiding crash.");

		THIS->SplitExp(exp, other);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_GroupMessage); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GroupMessage)
{
	dXSARGS;
	if ((items != 3) && (items != 4))	// the 3 item version is kept for backwards compatability
		Perl_croak(aTHX_ "Usage: Group::GroupMessage(THIS, sender, language, message)");
	{
		Group *		THIS;
		Mob*		sender;
		uint8		language;
		char*		message;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			sender = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "sender is not of type Mob");
		if(sender == NULL)
			Perl_croak(aTHX_ "sender is NULL, avoiding crash.");

		if (items == 4) {
			language = (uint8)SvUV(ST(2));
			if ((language >= MAX_PP_LANGUAGE) || (language < 0))
				language = 0;
			message = (char *)SvPV_nolen(ST(3));
			THIS->GroupMessage(sender, language, 100, message);
		}
		else {	// if no language is specificed, send it in common
			message = (char *)SvPV_nolen(ST(2));
			THIS->GroupMessage(sender,0, 100, message);
		}
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_GetTotalGroupDamage); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GetTotalGroupDamage)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::GetTotalGroupDamage(THIS, other)");
	{
		Group *		THIS;
		uint32		RETVAL;
		dXSTARG;
		Mob*		other;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			other = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "other is not of type Mob");
		if(other == NULL)
			Perl_croak(aTHX_ "other is NULL, avoiding crash.");

		RETVAL = THIS->GetTotalGroupDamage(other);
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Group_SplitMoney); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_SplitMoney)
{
	dXSARGS;
	if (items != 5)
		Perl_croak(aTHX_ "Usage: Group::SplitMoney(THIS, copper, silver, gold, platinum)");
	{
		Group *		THIS;
		uint32		copper = (uint32)SvUV(ST(1));
		uint32		silver = (uint32)SvUV(ST(2));
		uint32		gold = (uint32)SvUV(ST(3));
		uint32		platinum = (uint32)SvUV(ST(4));

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SplitMoney(copper, silver, gold, platinum);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_SetLeader); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_SetLeader)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::SetLeader(THIS, newleader)");
	{
		Group *		THIS;
		Mob*		newleader;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			newleader = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "newleader is not of type Mob");
		if(newleader == NULL)
			Perl_croak(aTHX_ "newleader is NULL, avoiding crash.");

		THIS->SetLeader(newleader);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_GetLeader); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GetLeader)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::GetLeader(THIS)");
	{
		Group *		THIS;
		Mob *		RETVAL;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetLeader();
		ST(0) = sv_newmortal();
		sv_setref_pv(ST(0), "Mob", (void*)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Group_GetLeaderName); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GetLeaderName)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::GetLeaderName(THIS)");
	{
		Group *		THIS;
		char *		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetLeaderName();
		sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
	}
	XSRETURN(1);
}

XS(XS_Group_SendHPPacketsTo); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_SendHPPacketsTo)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::SendHPPacketsTo(THIS, newmember)");
	{
		Group *		THIS;
		Mob*		newmember;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			newmember = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "newmember is not of type Mob");
		if(newmember == NULL)
			Perl_croak(aTHX_ "newmember is NULL, avoiding crash.");

		THIS->SendHPPacketsTo(newmember);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_SendHPPacketsFrom); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_SendHPPacketsFrom)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::SendHPPacketsFrom(THIS, newmember)");
	{
		Group *		THIS;
		Mob*		newmember;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			newmember = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "newmember is not of type Mob");
		if(newmember == NULL)
			Perl_croak(aTHX_ "newmember is NULL, avoiding crash.");

		THIS->SendHPPacketsFrom(newmember);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_IsLeader); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_IsLeader)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::IsLeader(THIS, leadertest)");
	{
		Group *		THIS;
		bool		RETVAL;
		Mob*		leadertest;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			leadertest = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "leadertest is not of type Mob");
		if(leadertest == NULL)
			Perl_croak(aTHX_ "leadertest is NULL, avoiding crash.");

		RETVAL = THIS->IsLeader(leadertest);
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_Group_GroupCount); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GroupCount)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::GroupCount(THIS)");
	{
		Group *		THIS;
		uint8		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GroupCount();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Group_GetHighestLevel); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GetHighestLevel)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::GetHighestLevel(THIS)");
	{
		Group *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetHighestLevel();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Group_TeleportGroup); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_TeleportGroup)
{
	dXSARGS;
	if (items != 7)
		Perl_croak(aTHX_ "Usage: Group::TeleportGroup(THIS, sender, zoneID, x, y, z, heading)");
	{
		Group *		THIS;
		Mob*		sender;
		uint32		zoneID = (uint32)SvUV(ST(2));
		float		x = (float)SvNV(ST(3));
		float		y = (float)SvNV(ST(4));
		float		z = (float)SvNV(ST(5));
		float		heading = (float)SvNV(ST(6));

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV*)SvRV(ST(1)));
			sender = INT2PTR(Mob *,tmp);
		}
		else
			Perl_croak(aTHX_ "sender is not of type Mob");
		if(sender == NULL)
			Perl_croak(aTHX_ "sender is NULL, avoiding crash.");

		THIS->TeleportGroup(sender, zoneID, 0, x, y, z, heading);
	}
	XSRETURN_EMPTY;
}

XS(XS_Group_GetID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Group_GetID)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Group::GetID(THIS)");
	{
		Group *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetID();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Group_GetMember);
XS(XS_Group_GetMember) 
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Group::GetMember(THIS, index)");
	{
		Group * THIS;
		Mob* member;
		Client*	RETVAL = NULL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Group")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Group *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Group");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		int index = (int)SvUV(ST(1));
		if (index < 0 || index > 5) 
			RETVAL = NULL;
		else {
			member = THIS->members[index];
			if (member != NULL)
				RETVAL = member->CastToClient();
		}

		ST(0) = sv_newmortal();
		sv_setref_pv(ST(0), "Client", (void*)RETVAL);
	}
	XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Group); /* prototype to pass -Wmissing-prototypes */
XS(boot_Group)
{
	dXSARGS;
	char file[256];
	strncpy(file, __FILE__, 256);
	file[255] = 0;
	
	if(items != 1)
		fprintf(stderr, "boot_quest does not take any arguments.");
	char buf[128];

	//add the strcpy stuff to get rid of const warnings....



	XS_VERSION_BOOTCHECK ;

		newXSproto(strcpy(buf, "DisbandGroup"), XS_Group_DisbandGroup, file, "$");
		newXSproto(strcpy(buf, "IsGroupMember"), XS_Group_IsGroupMember, file, "$$");
		newXSproto(strcpy(buf, "CastGroupSpell"), XS_Group_CastGroupSpell, file, "$$$");
		newXSproto(strcpy(buf, "SplitExp"), XS_Group_SplitExp, file, "$$$");
		newXSproto(strcpy(buf, "GroupMessage"), XS_Group_GroupMessage, file, "$$$");
		newXSproto(strcpy(buf, "GetTotalGroupDamage"), XS_Group_GetTotalGroupDamage, file, "$$");
		newXSproto(strcpy(buf, "SplitMoney"), XS_Group_SplitMoney, file, "$$$$$");
		newXSproto(strcpy(buf, "SetLeader"), XS_Group_SetLeader, file, "$$");
		newXSproto(strcpy(buf, "GetLeader"), XS_Group_GetLeader, file, "$");
		newXSproto(strcpy(buf, "GetLeaderName"), XS_Group_GetLeaderName, file, "$");
		newXSproto(strcpy(buf, "SendHPPacketsTo"), XS_Group_SendHPPacketsTo, file, "$$");
		newXSproto(strcpy(buf, "SendHPPacketsFrom"), XS_Group_SendHPPacketsFrom, file, "$$");
		newXSproto(strcpy(buf, "IsLeader"), XS_Group_IsLeader, file, "$$");
		newXSproto(strcpy(buf, "GroupCount"), XS_Group_GroupCount, file, "$");
		newXSproto(strcpy(buf, "GetHighestLevel"), XS_Group_GetHighestLevel, file, "$");
		newXSproto(strcpy(buf, "TeleportGroup"), XS_Group_TeleportGroup, file, "$$$$$$$");
		newXSproto(strcpy(buf, "GetID"), XS_Group_GetID, file, "$");
		newXSproto(strcpy(buf, "GetMember"), XS_Group_GetMember, file, "$$");
	XSRETURN_YES;
}

#endif //EMBPERL_XS_CLASSES

