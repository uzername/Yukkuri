/*
 * api.h
 *
 *  Created on: 21.09.2010
 */

#ifndef API_H_
#define API_H_

#include "Lua.h"

namespace scriptApi
{
	int ReadDirectory( lua_State* L );
	int GetCWD( lua_State* L );

	int Debug( lua_State* L );

	int SetBindings( lua_State* L );

	int CreateWidget( lua_State* L );
	int LoadWidget( lua_State* L );
	int ToggleWidget( lua_State* L );
	int GetWidgetName( lua_State* L );
	int BindWidget( lua_State* L );
	int BindWidgetMaxBar( lua_State* L );
	int WidgetChildren( lua_State* L );
	int WidgetSetBarSize( lua_State* L );

	int CreateUnit( lua_State* L );
	int DeleteUnit( lua_State* L );

	int NewThread( lua_State* L );
	int ThreadWait( lua_State* L );
	int ResumeThread( lua_State* L );
	int RemoveThread( lua_State* L );

	int SetCameraTarget( lua_State* L );

	int LoadMapRegion( lua_State* L );

}

#endif /* API_H_ */
