

#include "graphics/Camera.h"
#include "units/Unit.h"
#include "config.h"
#include <math.h>


extern MainConfig conf;


namespace {
	int TargetMode = ctmNormal;
	s2f pos;
	s2f offset;
	double* TargetX = NULL;
	double* TargetY = NULL;
	Unit* Target = NULL;
	s3f* MainView = NULL;
}



void Camera::init( s3f* view )
{
	MainView = view;
}


void Camera::Update( )
{
	MainView->x = -floor( pos.x - offset.x );
	MainView->y = -floor( pos.y - offset.y );
	if( TargetX && TargetY ){
		if( (*TargetX) != pos.x || (*TargetY) != pos.y ){
			Move( (float)(pos.x - (*TargetX)), (float)(pos.y - (*TargetY)) );
		}
	}
}


float Camera::GetX( )
{
	if( TargetX != NULL ){
		if( TargetMode == ctmCenter ){
			return *TargetX - ( conf.windowWidth / 2 );
		}
		return *TargetX;
	}
	return pos.x;
}


float Camera::GetY( )
{
	if( TargetY != NULL ){
		if( TargetMode == ctmCenter ){
			return *TargetY - ( conf.windowHeight / 2 );
		}
		return *TargetY;
	}
	return pos.y;
}


void Camera::Move( float x, float y )
{
	pos.x -= x;
	pos.y -= y;
}


void Camera::ChangeMode( enum ctMode mode )
{
	if( mode == TargetMode )
		return;
	TargetMode = mode;
	switch( mode ){
		case ctmCenter:
			offset.x = (float)(conf.windowWidth >> 1);
			offset.y = (float)(conf.windowHeight >> 1);
			break;
		case ctmNormal:
			offset.x = offset.y = 0;
			break;
	}
}


void Camera::SetTarget( Unit* u )
{
	DeleteTarget( );
	if( !u )
		return;
	Target = u;
	SetTarget( u->getUnitpX(), u->getUnitpY() );
}


void Camera::SetTarget( double* x, double* y )
{
	TargetX = x;
	TargetY = y;
	ChangeMode( ctmCenter );
	Update( );
}


Unit* Camera::GetTarget( )
{
	return Target;
}


void Camera::DeleteTarget( )
{
	Target = NULL;
	TargetX = NULL;
	TargetY = NULL;
	ChangeMode( ctmNormal );
}
