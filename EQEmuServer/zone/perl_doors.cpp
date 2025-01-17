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

#include "doors.h"

#ifdef THIS	 /* this macro seems to leak out on some systems */
#undef THIS		
#endif

XS(XS_Doors_GetDoorDBID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetDoorDBID)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetDoorDBID(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetDoorDBID();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetDoorID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetDoorID)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetDoorID(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetDoorID();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetID)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetID(THIS)");
	{
		Doors *		THIS;
		uint16		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetEntityID();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetX); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetX)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetX(THIS)");
	{
		Doors *		THIS;
		float		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetX();
		XSprePUSH; PUSHn((double)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetY); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetY)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetY(THIS)");
	{
		Doors *		THIS;
		float		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetY();
		XSprePUSH; PUSHn((double)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetZ)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetZ(THIS)");
	{
		Doors *		THIS;
		float		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetZ();
		XSprePUSH; PUSHn((double)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetHeading); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetHeading)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetHeading(THIS)");
	{
		Doors *		THIS;
		float		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetHeading();
		XSprePUSH; PUSHn((double)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetOpenType); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetOpenType)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetOpenType(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetOpenType();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetLockpick); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetLockpick)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetLockpick(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetLockpick();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetKeyItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetKeyItem)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetKeyItem(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetKeyItem();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetNoKeyring); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetNoKeyring)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::GetNoKeyring(THIS, type)");
	{
		Doors *		THIS;
		uint8		type = (uint8)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->GetNoKeyring();
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_GetIncline); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetIncline)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetIncline(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetIncline();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetSize); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetSize)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetIncline(THIS)");
	{
		Doors *		THIS;
		uint32		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetSize();
		XSprePUSH; PUSHu((UV)RETVAL);
	}
	XSRETURN(1);
}



XS(XS_Doors_SetOpenType); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetOpenType)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetOpenType(THIS, type)");
	{
		Doors *		THIS;
		uint32		type = (uint32)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetOpenType(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetLockpick); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetLockpick)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetLockpick(THIS, type)");
	{
		Doors *		THIS;
		uint32		type = (uint32)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetLockpick(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetKeyItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetKeyItem)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetKeyItem(THIS, type)");
	{
		Doors *		THIS;
		uint32		type = (uint32)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetKeyItem(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetNoKeyring); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetNoKeyring)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetNoKeyring(THIS, type)");
	{
		Doors *		THIS;
		uint8		type = (uint8)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetNoKeyring(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetIncline); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetIncline)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetIncline(THIS, type)");
	{
		Doors *		THIS;
		uint32		type = (uint32)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetIncline(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetSize); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetSize)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetSize(THIS, size)");
	{
		Doors *		THIS;
		uint32		type = (uint32)SvUV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetSize(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetLocation); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetLocation)
{
	dXSARGS;
	if (items != 4)
		Perl_croak(aTHX_ "Usage: Doors::SetLocation(THIS, x, y, z)");
	{
		Doors *		THIS;
		float		x = (float)SvNV(ST(1));
		float		y = (float)SvNV(ST(2));
		float		z = (float)SvNV(ST(3));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetLocation(x, y, z);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetX); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetX)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetX(THIS, XPos)");
	{
		Doors *		THIS;
		float		pos = (float)SvNV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetX(pos);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetY); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetY)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetY(THIS, YPos)");
	{
		Doors *		THIS;
		float		pos = (float)SvNV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetY(pos);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetZ)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetZ(THIS, ZPos)");
	{
		Doors *		THIS;
		float		pos = (float)SvNV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetZ(pos);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetHeading); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetHeading)
{
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetHeading(THIS, heading)");
	{
		Doors *		THIS;
		float		heading = (float)SvNV(ST(1));

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->SetHeading(heading);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetModelName); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetModelName)
{
	dXSARGS;
	if (items < 1 || items > 2)
		Perl_croak(aTHX_ "Usage: Doors::SetModelName(THIS, name)");
	{
		Doors *		THIS;
		char *		name = NULL;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		if (items > 1)	{	name = (char *)SvPV_nolen(ST(1));	}

		THIS->SetDoorName(name);
	}
	XSRETURN_EMPTY;
}
XS(XS_Doors_GetModelName); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetModelName)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetModelName(THIS)");
	{
		Doors *		THIS;
		Const_char *		RETVAL;
		dXSTARG;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		RETVAL = THIS->GetDoorName();
		sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
	}
	XSRETURN(1);
}

XS(XS_Doors_CreateDatabaseEntry); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_CreateDatabaseEntry)
{
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::InsertDoor(THIS)");
	{
		Doors *		THIS;

		if (sv_derived_from(ST(0), "Doors")) {
			IV tmp = SvIV((SV*)SvRV(ST(0)));
			THIS = INT2PTR(Doors *,tmp);
		}
		else
			Perl_croak(aTHX_ "THIS is not of type Doors");
		if(THIS == NULL)
			Perl_croak(aTHX_ "THIS is NULL, avoiding crash.");

		THIS->CreateDatabaseEntry();
	}
	XSRETURN_EMPTY;
}



#ifdef __cplusplus
extern "C"
#endif
XS(boot_Doors); /* prototype to pass -Wmissing-prototypes */
XS(boot_Doors)
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
		newXSproto(strcpy(buf, "GetID"),XS_Doors_GetID, file, "$");
		newXSproto(strcpy(buf, "SetModelName"),XS_Doors_SetModelName, file, "$$");
		newXSproto(strcpy(buf, "GetModelName"),XS_Doors_GetModelName, file, "$");
		newXSproto(strcpy(buf, "GetX"),XS_Doors_GetX, file, "$");
		newXSproto(strcpy(buf, "GetY"),XS_Doors_GetY, file, "$");
		newXSproto(strcpy(buf, "GetZ"),XS_Doors_GetZ, file, "$");
		newXSproto(strcpy(buf, "GetHeading"),XS_Doors_GetHeading, file, "$");
		newXSproto(strcpy(buf, "SetX"),XS_Doors_SetX, file, "$$");
		newXSproto(strcpy(buf, "SetY"),XS_Doors_SetY, file, "$$");
		newXSproto(strcpy(buf, "SetZ"),XS_Doors_SetZ, file, "$$");
		newXSproto(strcpy(buf, "SetHeading"),XS_Doors_SetHeading, file, "$$");
		newXSproto(strcpy(buf, "SetLocation"),XS_Doors_SetLocation, file, "$$$$");    
		newXSproto(strcpy(buf, "GetDoorDBID"),XS_Doors_GetDoorDBID, file, "$");
		newXSproto(strcpy(buf, "GetDoorID"),XS_Doors_GetDoorID, file, "$");
		newXSproto(strcpy(buf, "SetSize"),XS_Doors_SetSize, file, "$$");
		newXSproto(strcpy(buf, "GetSize"),XS_Doors_GetSize, file, "$");
		newXSproto(strcpy(buf, "SetIncline"),XS_Doors_SetIncline, file, "$$");
		newXSproto(strcpy(buf, "GetIncline"),XS_Doors_GetIncline, file, "$");
		newXSproto(strcpy(buf, "SetOpenType"),XS_Doors_SetOpenType, file, "$$");
		newXSproto(strcpy(buf, "GetOpenType"),XS_Doors_GetOpenType, file, "$");
		newXSproto(strcpy(buf, "SetLockPick"),XS_Doors_SetLockpick, file, "$$");
		newXSproto(strcpy(buf, "GetLockPick"),XS_Doors_GetLockpick, file, "$");
		newXSproto(strcpy(buf, "SetKeyItem"),XS_Doors_SetKeyItem, file, "$$");
		newXSproto(strcpy(buf, "GetKeyItem"),XS_Doors_GetKeyItem, file, "$");
		newXSproto(strcpy(buf, "SetNoKeyring"),XS_Doors_SetNoKeyring, file, "$$");
		newXSproto(strcpy(buf, "GetNoKeyring"),XS_Doors_GetNoKeyring, file, "$");
		newXSproto(strcpy(buf, "CreateDatabaseEntry"),XS_Doors_CreateDatabaseEntry, file, "$");
	XSRETURN_YES;
}
#endif //EMBPERL_XS_CLASSES
