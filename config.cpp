/*
 * config.cpp
 *
 *  Created on: 02.09.2010
 */

#include "config.h"
#include "Luaconfig.h"

MainConfig conf;

bool MainConfig::load( )
{
	LuaConfig* lc = LuaConfig::Instance();
	string subconfig;
	string config;
	subconfig = config = "general";
	lc->LoadAll( "config" );
	lc->getValue( "windows_width" , subconfig, config, windowWidth );
	lc->getValue( "windows_height" , subconfig, config, windowHeight );
	lc->getValue( "maximum_frame_rate" , subconfig, config, maxFrameRate );
	lc->getValue( "minimum_frame_rate" , subconfig, config, minFrameRate );

	lc->getValue( "images_path" , subconfig, config, imagePath );
	lc->getValue( "default_image_name" , subconfig, config, defaultImage );
	lc->getValue( "fonts_path" , subconfig, config, fontsPath );
	lc->getValue( "scripts_path" , subconfig, config, scriptsPath );
	lc->getValue( "configs_path" , subconfig, config, configsPath );

	lc->getValue( "widgets_z" , subconfig, config, widgetsPosZ );

	lc->getValue( "day_length" , subconfig, config, dayLength );
	lc->getValue( "action_interval" , subconfig, config, actionInterval );
	lc->getValue( "max_spawn" , subconfig, config, maxSpawn );
	lc->getValue( "max_edibles" , subconfig, config, maxEdibles );

	return true;
};
