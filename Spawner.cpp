/*
 * Spawner.cpp
 *
 *  Created on: 26.08.2010
 */
#include "Spawner.h"
#include "unitmanager.h"
#include "Define.h"
#include "Dynamic.h"
#include "config.h"

extern MainConfig conf;

void Spawner::Spawn( )
{
	/*float x, y;
	if( UnitManager::GetUnitsSize(utEntity) < conf.maxSpawn ){
		x = y = 0;
		getPosition( &x, &y );
		DynamicUnit* u = dynamic_cast<DynamicUnit*>( UnitManager::CreateUnit( utEntity, x, y ) );
		DynamicUnit* p = dynamic_cast<DynamicUnit*>( UnitManager::GetPlayer( ) );
		if( u && p ){
			float level = p->getUnitParameter("level");
			u->levelUp( rand( ) % static_cast<int>( level ? level : 1 ) + 3 );
		}
	}*/
	/*if( UnitManager::GetUnitsSize(PLANT) < conf.maxEdibles ){
		x = y = 0;
		getPosition( &x, &y );
		UnitManager::CreateUnit( PLANT, x, y );
	}*/
}

void Spawner::getPosition( float* retx, float* rety )
{
	Unit* player = UnitManager::GetPlayer();
	if( player )
	(*retx) = player->getUnitX() +
			( ( rand( ) % ( conf.windowWidth / 2) ) + conf.windowWidth / 2 ) * ( ( rand()%2 ) ? 1 : -1 );
	(*rety) = player->getUnitY() +
			( ( rand( ) % ( conf.windowHeight / 2) ) + conf.windowHeight / 2 ) * ( ( rand()%2 ) ? 1 : -1 );
}
