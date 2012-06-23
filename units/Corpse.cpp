/*
 * Corpse.cpp
 *
 *  Created on: 23.08.2010
 */

#include "Corpse.h"
#include "Render.h"

Corpse::Corpse( )
{
	blood = NULL;
}

Corpse::~Corpse( )
{
	RenderManager::Instance( )->FreeGLSprite( blood );
}

bool Corpse::Create( int id )
{
	if( !Unit::Create( id ) )
		return false;
	TextureInfo* t = Image.getSprite()->tex;
	if( t->rows > 1 || t->cols > 1 ){
		blood = RenderManager::Instance( )->CreateGLSprite( Image.getSprite() );
		blood->setPicture( Image.getPicture() + 1 );
	}
	return true;
}

void Corpse::setUnitPos( float x, float y )
{
	Plant::setUnitPos( x, y );
	if( blood ){
		blood->setPosition( getUnitX() - Image.getWidth() / 4, getUnitY(), Z - 0.1 );
		blood->resize( Image.getWidth() * getUnitSize(), Image.getHeight() * getUnitSize() );
	}
}

void Corpse::update( const int& dt )
{
	AnimatedUnit::update( dt );
	/*if( blood ){
		blood->setPosition( getUnitX() - getUnitWidth()/4 , getUnitY(), Z - 1 );
		if( !blood->coordinates ){
			getUnitImage( )->setPosition( 0, 0, Z - 1);
			blood->resize( getUnitWidth() * getUnitSize(), getUnitHeight() * getUnitSize() );
			blood->coordinates = Graphics::Instance( )->GetAnimation( getUnitName(), 1 );
		}
	}*/
}
