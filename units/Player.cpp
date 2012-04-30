#include "Player.h"
#include "config.h"

extern MainConfig conf;

Player::Player()
{
	moveX = 0;
	moveY = 0;

	FoodTypes.push_back( "corpse" );
}

void Player::Die( )
{
	if( conf.playerDies ){
		DynamicUnit::Die( );
	}
}

void Player::moveUnit( short axis, signed int val )
{
	if( axis )
		moveX = val;
	else
		moveY = val;
	if( moveX == 0 && moveY == 0 )
		Image.setDefault();
}

void Player::update( const int& dt )
{
	DynamicUnit::update( dt );
	if( this->isDeleted() )
		return;
	DynamicUnit::moveUnit( moveX, moveY, dt );
}
