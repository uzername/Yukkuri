/*
 * CUDataBind.h
 *
 *  Created on: 19.05.2012
 *
 */

//////////////////////////////////////////////////////////////////////////
//
// How to add new class?
// 1. Put name of class in typelist ClassesList (the order of classes is important, they enumerated from 0).
//    Class must implement createUData virtual function from CUDataUser class
// 2. Declare the function for userdata creation (use UDATA_CREATOR_FUNC_DECL macro)
// 3. Add RegisterTypeMetatable call for new class in RegisterAllTypeMetatables function.
//
//////////////////////////////////////////////////////////////////////////
//
// 4-a. How to add new getter for field?
//    Add GETTER_METHOD_DECL(field_name)
//    Add GETTER_METHOD_ENTRY(number, field_name) in ud_meta array, where
//      number is number of class in ClassesList typelist;
//      field_name is name of public field in this class
// 4-b. How to add new getter/setter for field?
//    Add GETSET_METHOD_DECL(field_name)
//    Add GETSET_METHOD_ENTRY(number, field_name) in ud_meta array, where
//      number is number of class in ClassesList typelist;
//      field_name is name of public field in this class
//
// There are more declaration macros like GETSET_METHOD_DECL in 3rdparty/CUData.cpp.
//
// If there is field with equal names in different classes, only one declaration must be.
// METAMETHODS_MAX_COUNT value can be increased, if needed.
//
//////////////////////////////////////////////////////////////////////////
//
// Structure of this file:
// This file consists of several include blocks. This helps to separate implementation details
// from declarations and to simplify the maintance of the code.
// This file is included by the udata.cpp only.


#if INCLUDE_BLOCK == 1

// Includes of declarations of all types in typelist
/* Units */
#include "units/Unit.h"
#include "units/UnitDynamic.h"
#include "units/UnitEntity.h"
#include "units/UnitCorpse.h"
#include "units/UnitPlayer.h"

/* Widgets */
#include "interface/widgets/Widget.h"
#include "interface/widgets/WidgetText.h"
#include "interface/widgets/WidgetBar.h"

// Typelist with all types, that can be passed to lua as userdata
typedef TYPELIST_9( Unit, UnitStatic, UnitDynamic, Entity, Corpse, Player, Widget, WidgetText, WidgetBar ) ClassesList;



#elif INCLUDE_BLOCK == 2

// 2. For each type, it's needed to explicitly declare functions for userdata creation.
UDATA_CREATOR_FUNC_DECL(Unit);
UDATA_CREATOR_FUNC_DECL(UnitStatic);
UDATA_CREATOR_FUNC_DECL(UnitDynamic);
UDATA_CREATOR_FUNC_DECL(Entity);
UDATA_CREATOR_FUNC_DECL(Corpse);
UDATA_CREATOR_FUNC_DECL(Player);

UDATA_CREATOR_FUNC_DECL(Widget);
UDATA_CREATOR_FUNC_DECL(WidgetText);
UDATA_CREATOR_FUNC_DECL(WidgetBar);



#elif INCLUDE_BLOCK == 3

// 3. Registration of metatables
// This functions will be called on lua initialization in SCRIPT::InitScript
void RegisterAllTypeMetatables(lua_State* L)
{
	// Please, don't change this line
	std::fill(udata_refs, udata_refs + TL::Length<ClassesList>::value, LUA_NOREF);

	// Make RegisterTypeMetatable calls for each type
	RegisterTypeMetatable<Unit>(L);
	RegisterTypeMetatable<UnitStatic>(L);
	RegisterTypeMetatable<UnitDynamic>(L);
	RegisterTypeMetatable<Entity>(L);
	RegisterTypeMetatable<Corpse>(L);
	RegisterTypeMetatable<Player>(L);

	RegisterTypeMetatable<Widget>(L);
	RegisterTypeMetatable<WidgetText>(L);
	RegisterTypeMetatable<WidgetBar>(L);

}


#elif INCLUDE_BLOCK == 4

// 4. Declaration of methods in metatables

// Declarations

// Units
#define DECL_UNIT_METH									\
		GETSETF_METHOD_DECL(UnitName)					\
		GETSETF_METHOD_DECL(UnitX)						\
		GETSETF_METHOD_DECL(UnitY)						\
		GETSETF_METHOD_DECL(UnitSize)					\
		GETTERF_METHOD_DECL(UnitId)						\
		GETTERF_METHOD_DECL(UnitName)					\
		GETTERF_METHOD_DECL(UnitTypeName)				\
		GETTERF_METHOD_DECL(UnitSize)					\
		EXEC_METHOD_DECL(color)

#define DECL_UNITSTATIC_METH

#define DECL_UNITDYNAMIC_METH							\
		GETSET_FLAG_METHOD_DECL(Scope)

#define DECL_UNITENTITY_METH
#define DECL_UNITCORPSE_METH
#define DECL_UNITPLAYER_METH


// Widgets
#define DECL_WIDGET_METH								\
		EXEC_METHOD_DECL(resize)						\
		EXEC_METHOD_DECL(toggle)						\
		EXEC_METHOD_DECL(bindParam)						\
		EXEC_NAMED_METHOD_DECL(children, getChildren)

#define DECL_WIDGETTEXT_METH							\
		EXEC_METHOD_DECL(setText)						\
		GETTERF_METHOD_DECL(Lines)						\
		GETTERF_METHOD_DECL(LineSize)					\
		GETSETF_METHOD_DECL(LineHeight)					\
		GETSETF_METHOD_DECL(Cursor)						\
		GETSET_FLAG_METHOD_DECL(CursorVisible)

#define DECL_WIDGETBAR_METH								\
		GETSETF_METHOD_DECL(BarSize)					\
		EXEC_METHOD_DECL(bindBarMaxValue)



DECL_UNIT_METH
DECL_UNITDYNAMIC_METH
DECL_UNITENTITY_METH
DECL_UNITCORPSE_METH
DECL_UNITPLAYER_METH
DECL_WIDGET_METH
DECL_WIDGETTEXT_METH
DECL_WIDGETBAR_METH



// Metatable records


// Units
#define UNIT_METH_ENTRY(ID)						\
		GETSET_METHOD_ENTRY(ID, UnitName)		\
		GETSET_METHOD_ENTRY(ID, UnitX)			\
		GETSET_METHOD_ENTRY(ID, UnitY)			\
		GETSET_METHOD_ENTRY(ID, UnitSize)		\
		GETTER_METHOD_ENTRY(ID, UnitId)			\
		GETTER_METHOD_ENTRY(ID, UnitName)		\
		GETTER_METHOD_ENTRY(ID, UnitTypeName)	\
		GETTER_METHOD_ENTRY(ID, UnitSize)		\
		EXEC_METHOD_ENTRY(ID, color)

#define UNITSTATIC_METH_ENTRY(ID)				\
		UNIT_METH_ENTRY(ID)

#define UNITDYNAMIC_METH_ENTRY(ID)				\
		UNIT_METH_ENTRY(ID)						\
		GETSET_METHOD_ENTRY(ID, Scope)

#define UNITENTITY_METH_ENTRY(ID)				\
		UNITDYNAMIC_METH_ENTRY(ID)
#define UNITCORPSE_METH_ENTRY(ID)				\
		UNITSTATIC_METH_ENTRY(ID)
#define UNITPLAYER_METH_ENTRY(ID)				\
		UNITDYNAMIC_METH_ENTRY(ID)


// Widgets
#define WIDGET_METH_ENTRY(ID)					\
		EXEC_METHOD_ENTRY(ID, resize)			\
		EXEC_METHOD_ENTRY(ID, toggle)			\
		EXEC_METHOD_ENTRY(ID, bindParam)		\
		EXEC_NAMED_METHOD_ENTRY(ID, children)


#define WIDGETTEXT_METH_ENTRY(ID)				\
		WIDGET_METH_ENTRY(ID)					\
		EXEC_METHOD_ENTRY(ID, setText)			\
		GETTER_METHOD_ENTRY(ID, Lines)			\
		GETTER_METHOD_ENTRY(ID, LineSize)		\
		GETSET_METHOD_ENTRY(ID, LineHeight)		\
		GETSET_METHOD_ENTRY(ID, Cursor)			\
		GETSET_METHOD_ENTRY(ID, CursorVisible)


#define WIDGETBAR_METH_ENTRY(ID)				\
		WIDGETTEXT_METH_ENTRY(ID)				\
		EXEC_METHOD_ENTRY(ID, bindBarMaxValue)	\
		GETSET_METHOD_ENTRY(ID, BarSize)



// Meta methods
const size_t METAMETHODS_MAX_COUNT = 70;
static const struct luaL_reg ud_meta[TL::Length<ClassesList>::value][METAMETHODS_MAX_COUNT] = {
	{
		STD_METHODS(0),
		UNIT_METH_ENTRY(0)
		END
	},
	{
		STD_METHODS(1),
		UNITSTATIC_METH_ENTRY(1)
		END
	},
	{
		STD_METHODS(2),
		UNITDYNAMIC_METH_ENTRY(2)
		END
	},
	{
		STD_METHODS(3),
		UNITENTITY_METH_ENTRY(3)
		END
	},
	{
		STD_METHODS(4),
		UNITCORPSE_METH_ENTRY(4)
		END
	},
	{
		STD_METHODS(5),
		UNITPLAYER_METH_ENTRY(5)
		END
	},
	{
		STD_METHODS(6),
		WIDGET_METH_ENTRY(6)
		END
	},
	{
		STD_METHODS(7),
		WIDGETTEXT_METH_ENTRY(7)
		END
	},
	{
		STD_METHODS(8),
		WIDGETBAR_METH_ENTRY(8)
		END
	}

};



#endif
