/*
 * GLTextures.cpp
 *
 *  Created on: 17.07.2012
 *
 */


#include "graphics/render/GLTextures.h"
#include "graphics/sdl_graphics.h"
#include <map>

#include "hacks.h"
#include "debug.h"


namespace {

	std::map < std::string, Texture* > texturesCache;

}


void GLTextures::add( std::string name, Texture* texture )
{
	Texture* cached;
	if( !texture )
		return;
	cached = get( name );
	if( cached == texture )
		return;
	GLTextures::free( cached );
	texturesCache[name] = texture;
}


void GLTextures::free( Texture* tex )
{
	if( tex && tex->tex ){
		glDeleteTextures( 1, &tex->tex );
		delete tex;
		tex = NULL;
	}
}


Texture* GLTextures::get( std::string name )
{
	std::map < std::string, Texture* >::iterator it;
	it = texturesCache.find(name);
	if( it != texturesCache.end() ){
		return it->second;
	}
	return NULL;
}


Texture* GLTextures::load( std::string name )
{
	Texture* tex;
	SDL_Surface* surface;

	if( name == "" )
		return NULL;

	tex = get( name );

	if( !tex ){

		surface = SDLGraphics::LoadImage( name.c_str() );

		if( !surface ){
			Debug::debug( Debug::GRAPHICS, name + " not loaded.\n" );
			return NULL;
		}

		tex = new Texture();
		tex->tex = SDLGraphics::CreateGlTexture( surface );
		tex->w = surface->w;
		tex->h = surface->h;

		add( name,  tex );

		if( surface )
			SDL_FreeSurface( surface );
	}

	return tex;
}




void GLTextures::clearCache( )
{
	FOREACHIT( texturesCache ){
		GLTextures::free( it->second );
		it->second = NULL;
	}
	texturesCache.clear();
}

