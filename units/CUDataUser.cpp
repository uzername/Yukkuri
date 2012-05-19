/*
 * CUDataUser.cpp
 *
 *  Created on: 17.05.2012
 *
 */

#include "units/CUDataUser.h"
#include "units/CUData.h"

#include "scripts/LuaScript.h"

#include "debug.h"


CUDataUser::~CUDataUser()
{
	if( pUdata )
		pUdata->clearUser();
}


int CUDataUser::pushUData( lua_State* L )
{
	if( !pUdata ){
		pUdata = this->createUData();
	}

	if( !pUdata ){
		Debug::debug( Debug::SCRIPT, "CUDataUser::pushUData: userdata creation failed" );
		return 0;
	}else{
		extern LuaScript* luaScript;
		luaScript->GetFromRegistry( L, pUdata->getRegRef() );
		return 1;
	}
}
