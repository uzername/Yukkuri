/*
 * TextureArray.h
 *
 *  Created on: 28.05.2012
 *
 */

#ifndef TEXTUREARRAY_H_
#define TEXTUREARRAY_H_

#include "graphics/GraphicsTypes.h"
#include <vector>

namespace TextureArray
{
	// Vertex buffer object
	VBOStructureHandle* prepareVBO( int* c, std::vector< Sprite* >& sprites, VertexV2FT2FC4UI* verticles );
	VBOStructureHandle* prepareVBO( int* c, Sprite* sprites, unsigned int scount, VertexV2FT2FC4UI* verticles );


	bool drawToNewGLTexture( GLuint* ahandle, int width, int height, std::vector< TextureProxy* >& textures );
	bool drawToNewGLTexture( GLuint* ahandle, int width, int height, Sprite* sprites, unsigned int count );
	bool drawToGLTexture( GLuint ahandle, std::vector< TextureProxy* >& textures );


}


#endif /* TEXTUREARRAY_H_ */
