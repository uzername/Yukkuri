#ifndef YDEFINE_H
#define YDEFINE_H

#define JOYSTICKENABLE
#define JSSENS 1000

//Render only visible in window
#define RENDER_VISIBLE
#define TIMEREVENTTICK 10

#ifndef MAX_PATH
	#define MAX_PATH 4096
#endif

#ifdef WIN32
	#undef GL_GLEXT_PROTOTYPES
	#include "GL\glew.h"
#else
	#define GL_GLEXT_PROTOTYPES 1
	#include "SDL/SDL_opengl.h"
#endif

#endif //YDEFINE_H
