/*
 * api.cpp
 *
 *  Created on: 21.09.2010
 */

#include "api.h"
#include "Interface.h"
#include "widgets/BarWidget.h"
#include "Bindings.h"
#include "LuaConfig.h"
#include "unitmanager.h"
#include "LuaThread.h"
#include "Camera.h"
#include "map.h"
#include <string>
#include <cstring>
#include <dirent.h>

#include "debug.h"
using namespace Debug;


int scriptApi::ReadDirectory( lua_State* L )
{
	DIR *dp;
	struct dirent *ep;
	std::string dirname;
	int top;
	int count = 0;

	luaL_argcheck( L, lua_isstring( L, 1 ), 1, "Directory name not given." );

	dirname = lua_tostring( L, 1 );

	dp = opendir(dirname.c_str());
	if( dp != NULL ){
		lua_newtable( L );
		top = lua_gettop( L );
		while ( (ep = readdir( dp ) ) != NULL) {
			lua_pushinteger( L, ++count );
			lua_pushstring( L, ep->d_name );
			lua_settable( L, top );
		}
	}else{
		lua_pushnil( L );
	}
	closedir( dp );


	return 1;
}

int scriptApi::GetCWD( lua_State* L )
{
	char path[1026];

	memset( path, '\0', sizeof(path) );

	if( getcwd( path, sizeof(path) - 1 ) == NULL ){
		lua_pushnil( L );
	}else{
		lua_pushstring( L, path );
	}

	return 1;
}


int scriptApi::Debug( lua_State* L )
{
	enum dbg_level level;
	std::string str;
	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Debug level expected." );
	luaL_argcheck( L, lua_isstring( L, 2 ), 2, "Debug string expected." );

	level = static_cast<enum dbg_level>(lua_tointeger( L, 1 ));
	str = lua_tostring( L, 2 );
	debug( level, str + "\n" );
	lua_pop( L, lua_gettop( L ) );
	return 0;
}

int scriptApi::SetBindings( lua_State* L )
{
	std::string bname;
	luaL_argcheck( L, lua_isstring( L, 1 ), 1, "Bindings id not given." );

	bname = lua_tostring( L, 1 );

	Bindings::bnd.LoadKeys( bname );

	return 0;
}

int scriptApi::CreateWidget( lua_State* L )
{
	return 0;
}

int scriptApi::LoadWidget( lua_State* L )
{
	std::string wname;

	luaL_argcheck( L, lua_isstring( L, 1 ), 1, "Widget name not given." );

	wname = lua_tostring( L, 1 );
	Widget* w = UI::yui.LoadWidget( wname );
	lua_pop( L, lua_gettop( L ) );
	if( !w ){
		lua_pushnil( L );
	}else{
		lua_pushinteger( L, w->getId( ) );
	}
	return 1;
}

int scriptApi::ToggleWidget( lua_State* L )
{
	Widget* w;
	bool visibility;
	bool result;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id not given." );

	w = UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) );
	visibility = w->getVisible();

	if( lua_isboolean( L, 2 ) )
		result = lua_toboolean( L, 2 );
	else
		result = !visibility;

	if( visibility != result )
		w->toggleVisibility();

	lua_pop( L, lua_gettop( L ) );
	lua_pushboolean( L, result );

	return 1;
}

int scriptApi::BindWidget( lua_State* L )
{
	Widget* w;
	Unit* u;
	std::string param;
	bool result;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id not given." );
	luaL_argcheck( L, lua_isnumber( L, 2 ), 2, "Unit id not given." );
	luaL_argcheck( L, lua_isstring( L, 3 ), 3, "Parameter not given." );


	w = UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) );
	u = UnitManager::GetUnit( static_cast<int>(lua_tointeger( L, 2 )) );
	param = lua_tostring( L, 3 );
	result = false;
	if( w && u && param != "" )
		result = w->bindValue( u->getUnitpParameter( param ) );
	lua_pop( L, lua_gettop( L ) );
	lua_pushboolean( L, result );
	return 1;
}

int scriptApi::BindWidgetMaxBar( lua_State* L )
{
	BarWidget* w;
	Unit* u;
	std::string param;
	bool result;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id not given." );
	luaL_argcheck( L, lua_isnumber( L, 2 ), 2, "Unit id not given." );
	luaL_argcheck( L, lua_isstring( L, 3 ), 3, "Parameter not given." );

	result = false;

	w = dynamic_cast<BarWidget*>( UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) ) );
	if( w ){
		u = UnitManager::GetUnit( static_cast<int>(lua_tointeger( L, 2 )) );
		param = lua_tostring( L, 3 );
		if( u && param != "" )
			result = w->bindBarMaxValue( u->getUnitpParameter( param ) );
	}
	lua_pop( L, lua_gettop( L ) );
	lua_pushboolean( L, result );
	return 1;
}

int scriptApi::WidgetChildren( lua_State* L )
{
	Widget* w;
	int csize;
	int top;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id not given." );

	w = UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) );
	lua_pop( L, lua_gettop( L ) );
	if( w ){
		csize = w->childrenCount( );
		Widget** children = (Widget**)malloc( sizeof(Widget*) * csize );
		w->getChildren( children, csize );
		lua_newtable( L );
		top = lua_gettop( L );
		for( int i = 0; i < csize; ++i ){
			lua_pushstring( L, children[i]->getName( ).c_str( ) );
			lua_pushinteger( L, children[i]->getId( ) );
			lua_settable( L, top );
		}
		free(children);
	}else{
		lua_pushboolean( L, false );
	}
	return 1;
}

int scriptApi::GetWidgetName( lua_State* L )
{
	Widget* w;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id expected." );

	w = UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) );
	lua_pop( L, lua_gettop( L ) );
	if( w ){
		lua_pushstring( L, w->getName().c_str() );
	}else{
		lua_pushnil( L );
	}
	return 1;
}

int scriptApi::WidgetSetBarSize( lua_State* L )
{
	Widget* w;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Widget id not given." );
	luaL_argcheck( L, lua_isnumber( L, 2 ), 2, "Bar maximum value expected." );

	w = UI::yui.GetWidget( static_cast<int>(lua_tointeger( L, 1 )) );
	if( w )
		w->setBarSize( static_cast<float>(lua_tonumber( L, 2 )) );
	lua_pop( L, lua_gettop( L ) );

	return 0;
}


int scriptApi::DeleteUnit( lua_State* L )
{
	unsigned int id;
	Unit* u;

	luaL_argcheck( L, lua_isnumber( L, 1 ), 1, "Unit id not given." );

	id = static_cast<int>(lua_tointeger( L, 1 ));
	u = UnitManager::GetUnit( id );
	lua_pop( L, lua_gettop( L ) );
	if( !id || !u ){
		lua_pushboolean( L, false );
		return 1;
	}
	UnitManager::DeleteUnit( u );
	lua_pushboolean( L, true );

	return 1;
}

int scriptApi::NewThread( lua_State* L )
{
	luaL_argcheck(L, lua_isfunction(L, 1), 1, "Function expected.");
	luaL_argcheck(L, lua_isboolean(L, 2) || lua_isnoneornil(L, 2), 2, "Boolean or none expected.");
	threadsManager::NewThread(L);
	return 1;
}

int scriptApi::ThreadWait( lua_State* L )
{
	return threadsManager::ThreadWait( L );
}

int scriptApi::ResumeThread( lua_State* L )
{
	return threadsManager::ResumeThread( L );
}

int scriptApi::RemoveThread( lua_State* L )
{
	unsigned int tid;
	luaL_argcheck( L, lua_isthread(L, 1), 1, "Thread expected" );
	lua_State* t = lua_tothread( L, 1 );
	tid = threadsManager::GetThread( t );
	if( tid > 0 ){
		lua_pushboolean( L, threadsManager::RemoveThread( tid ) );
		return 1;
	}else{
		lua_pushboolean( L, 0 );
		lua_pushstring( L, "Thread is not registered" );
		return 2;
	}
}

int scriptApi::SetCameraTarget( lua_State* L )
{
	unsigned int tid;
	Unit* u;
	luaL_argcheck(L, lua_isnumber(L, 1) || lua_isnoneornil(L, 1), 1, "Number or none expected.");
	tid = static_cast<int>(lua_tointeger( L, 1 ));
	u = UnitManager::GetUnit( tid );
	YCamera::CameraControl.SetTarget( u );
	return 0;
}


int scriptApi::LoadMapRegion(lua_State *L)
{
	std::string name;
	extern Map map;
	luaL_argcheck( L, lua_isstring( L, 1 ), 1, "Parameter not given." );
	name = lua_tostring( L, 1 );
	map.Load( name );
	return 0;
}


