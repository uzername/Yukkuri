/*
 * handlers.cpp
 *
 *  Created on: 24.07.2012
 *
 */

#include "units/physics/handlers.h"
#include "units/UnitDynamic.h"


int DynamiUint_begin( cpArbiter* arb, cpSpace* space, void* unused )
{
	cpShape *a, *b;
	cpArbiterGetShapes(arb, &a, &b);

	UnitDynamic* ua = reinterpret_cast<UnitDynamic*>(a->body->data);
	Unit* ub = reinterpret_cast<Unit*>(b->body->data);

	if( ua && ub )
		ua->Collisions.push( ub );

	return 0;
}


void DynamiUint_separate( cpArbiter* arb, cpSpace* space, void* unused )
{
	cpShape *a, *b;
	cpArbiterGetShapes(arb, &a, &b);

	UnitDynamic* ua = reinterpret_cast<UnitDynamic*>(a->body->data);
	Unit* ub = reinterpret_cast<Unit*>(b->body->data);

	if( ua && ub )
		ua->Collisions.remove( ub );

}

