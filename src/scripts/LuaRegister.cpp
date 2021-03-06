/*
 * LuaBase.cpp
 *
 *  Created on: 30.04.2012
 *
 */

#include "Lua.h"

#include "3rdparty/CUDataTemplates.h"

#include "api.h"
#include "api/UnitManagerApi.h"
#include "api/InterfaceApi.h"
#include "api/ThreadManagerApi.h"
#include "api/CameraApi.h"
#include "api/BindingsApi.h"
#include "api/PathsApi.h"

#include "units/Prototypes.h"
#include "units/Unit.h"
#include "units/YOBA.h"

#include "Bindings.h"
#include "misc.h"



#include "debug.h"


void LuaMain::RegisterApi( lua_State* L )
{
	// Register UData metatables
	RegisterAllTypeMetatables( L );


	// Register base methods
	lua_register( L, "readdir", &scriptApi::ReadDirectory );
	lua_register( L, "getcwd", &scriptApi::GetCWD );

	lua_register( L, "Debug", &scriptApi::Debug );

	lua_register( L, "LoadMapRegion", &scriptApi::LoadMapRegion );



#define REGAPI(name, api) luaL_register( L, name, api::methods );

	// Libraries
	REGAPI( "Interface", IfaceApi )
	REGAPI( "UnitManager", UMApi )
	REGAPI( "Input", BindingsApi )
	REGAPI( "Thread", ThreadApi )
	REGAPI( "Camera", CameraApi )
	REGAPI( "Paths", PathsApi )

#undef REGAPI



	// Регистрируем константные названия для клавиш.
	lua_newtable( L );			// Создаем новую таблицу. Стек: таблица
	{
		for( UINT i = 1; i < MAXKEYS; i++){		// Цикл по всем возможным кодам
			lua_pushinteger( L, i );		// Помещаем в стек код клавиши. Стек: таблица, i
			lua_setfield( L, -2, Bindings::keyName(i) ); // Заносим в таблицу перменную с именем и значением. Стек: таблица
		}
	}
	lua_setglobal(L, "keys");		// Заносим таблицу в глобальную переменную. Стек:


	lua_newtable(L);			// Создаем новую таблицу. Стек: таблица
	{
		for( int i = 0; i < Binds::bndLast; i++ ){		// Цикл по всем возможным функциям в конфиге
			lua_pushinteger( L, i );
			lua_setfield( L, -2, Binds::getFunctionName( (Binds::func_numbers)i ) );
		}
	}
	lua_setglobal(L, "bindings");		// Заносим таблицу в глобальную переменную. Стек:


#define FIELD(name) \
	lua_pushinteger( L, name ); lua_setfield( L, -2, #name );

	// Различные именованые константы
	lua_newtable(L);		// Стек: таблица
	{
		// Unit Types
		FIELD(utStatic)
		FIELD(utPlayer)
		FIELD(utEntity)
		FIELD(utPlant)
		FIELD(utCorpse)

		// Physics objects types
		FIELD(potNone)
		FIELD(potCircle)
		FIELD(potQuad)
		FIELD(potRectangle)
		FIELD(potPolygon)
		// Physics objects parameters types
		FIELD(pptMat)
		FIELD(pptRadius)
		FIELD(pptSides)


		// ***********************
		// Actions
		FIELD(acNone)

		// Action parameters stack
		FIELD(acPush)
		FIELD(acPushInt)
		FIELD(acPushFloat)
		FIELD(acPushString)


		// Functions
		FIELD(acSuper)
		FIELD(acRestoreState)
		FIELD(acSetAction)
		FIELD(acSetTimer)

		// Conditions
		FIELD(acCondition)
		FIELD(acIfParamEqual)
		FIELD(acIfParamLess)
		FIELD(acIfParamMore)
		FIELD(acIfParametersEqual)
		FIELD(acIfParametersLess)
		FIELD(acIfParametersMore)
		FIELD(acIfParametersLessBy)
		FIELD(acIfFlag)
		FIELD(acIfNotFlag)
		FIELD(acEnd)

		// Unit flags
		FIELD(ufDeleted)
		FIELD(ufEdible)
		FIELD(ufMoving)
		FIELD(ufLast)
		FIELD(acSetFlag)
		FIELD(acRemoveFlag)

		// Unit Parameters
		FIELD(acSetParam)
		FIELD(acCopyParam)
		FIELD(acLoadParam)
		FIELD(acLoadParamBunch)

		// Physics objects
		FIELD(acSetUnitPhysics)
		FIELD(acSetPhysicsLayer)

		// Misc commands
		FIELD(acMove)
		FIELD(acSetUnitSize)
		FIELD(acSetColor)
		FIELD(acDAddFood)
		FIELD(acDUnitGrow)
		FIELD(acEAddPathTarget)

		// Unit base parameters
		FIELD(uBaseLevel)
		FIELD(uBaseAge)
		FIELD(uBaseKills)
		// Unit attributes
		FIELD(uAttrStrength)
		FIELD(uAttrIntelligence)
		FIELD(uAttrAgility)
		FIELD(uAttrLuck)
		// Unit characteristics
		FIELD(uChrSpeed)
		FIELD(uChrDamage)
		FIELD(uChrDefence)
		FIELD(uChrNutritive)
		// Unit parametes
		FIELD(uParamHP)
		FIELD(uParamExp)
		FIELD(uParamFed)
		// Unit state
		FIELD(uStateHP)
		FIELD(uStateExp)
		FIELD(uStateFed)

	}
	lua_setglobal(L, "constants");		// Заносим таблицу в глобальную переменную. Стек:

#undef FIELD

}

void LuaMain::RegisterLib( std::string name, const luaL_Reg* functions )
{
	luaL_register( Lst, name.c_str(), functions );
}
