#include <stdlib.h>
#include <stdio.h>
#include "yukkuri.h"


// Entry point
int main(int argc, char* argv[])  // <- this must match exactly, since SDL rewrites it
{
	Yukkuri Engine;

	Engine.Init();

	Engine.SetTitle( "Yukkuri game" );
	Engine.Start();

	Engine.SetTitle( "Quitting..." );

	return 0;
}


void Yukkuri::AdditionalInit()
{
	//map.Init("map.map");
	cout << "Additional Init" << endl;

	LuaConfig::conf.LoadAll( "config" );

	Bindings::bnd.setEngine( this );

	Bindings::bnd.LoadKeys();

	LuaConfig::conf.LoadAll( "widget" );
	UI::yui.LoadAllWidgets( );

	daytime.loadInterface();

	LuaConfig::conf.LoadAll( "entity" );

	units = &UnitManager::units;

	for( int i=0; i < ( rand() % 100 ); i++){
		units->CreateUnit( ENTITY, 2, 2 );
	}

	//FIXME: input blocked if player loads first
	units->CreateUnit( PLAYER, 0, 0 );
	YCamera::CameraControl.SetTarget( units->GetPlayer()->getUnitpX(), units->GetPlayer()->getUnitpY());
}

void Yukkuri::Think( const int& ElapsedTime )
{
	// Do time-based calculations
	units->tick( ElapsedTime );
	daytime.update( ElapsedTime );

}

void Yukkuri::Render( )
{
	Graphics::graph.CleanGLScene( );

	// Display slick graphics on screen
	units->DrawUnits( YCamera::CameraControl.GetX(), YCamera::CameraControl.GetY() );

	daytime.draw( );

	UI::yui.GetWidget("fps")->setText(GetFPSText());
	UI::yui.DrawWidgets( );

	//Draw to screen
	Graphics::graph.DrawGLScene( );
}

void Yukkuri::MouseMoved( const int& Button, const int& X, const int& Y, const int& RelX, const int& RelY )
{
	// Handle mouse movement

	// X and Y are absolute screen positions
	// RelX and RelY are screen position relative to last detected mouse movement
}

void Yukkuri::MouseButtonUp( const int& Button, const int& X, const int& Y, const int& RelX, const int& RelY )
{
	// Handle mouse button released
}

void Yukkuri::MouseButtonDown( const int& Button, const int& X, const int& Y, const int& RelX, const int& RelY )
{
	// Handle mouse button pressed
}

void Yukkuri::WindowInactive()
{
	// Pause game
}

void Yukkuri::WindowActive()
{
	// Un-pause game
}

void Yukkuri::End()
{
	// Clean up
}
