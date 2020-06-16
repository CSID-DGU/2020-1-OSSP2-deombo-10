#include "define.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>


#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iostream>//출력 테스트를 위해서 추가

/*
socket programming을 위하여 추가되 해더
*/
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <list>
#include <malloc.h>


using namespace std;


bool intersects(SDL_Rect a, SDL_Rect b);//충돌 감지


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

SDL_Surface *load_image( std::string filename );

void DrawPixel(SDL_Surface* Target, Sint16 X, Sint16 Y, Uint16 Color); //Draws the specified color at the specified X and Y on the target surface.
Uint32 ReadPixel(SDL_Surface* Source, Sint16 X, Sint16 Y); //Returns the color of the specified surface on the specified X and Y coordinates.

SDL_Surface* SDL_ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);

/*  

SDL_rotozoom.c: rotozoomer, zoomer and shrinker for 32bit or 8bit surfaces

Copyright (C) 2001-2012  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/

#ifndef _SDL_rotozoom_H
#define _SDL_rotozoom_H



/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef M_PI
#define M_PI	3.141592654
#endif



	/* ---- Defines */

	/*!
	\brief Disable anti-aliasing (no smoothing).
	*/
#define SMOOTHING_OFF		0

	/*!
	\brief Enable anti-aliasing (smoothing).
	*/
#define SMOOTHING_ON		1

	/* ---- Function Prototypes */

#ifdef _MSC_VER
#  if defined(DLL_EXPORT) && !defined(LIBSDL_GFX_DLL_IMPORT)
#    define SDL_ROTOZOOM_SCOPE __declspec(dllexport)
#  else
#    ifdef LIBSDL_GFX_DLL_IMPORT
#      define SDL_ROTOZOOM_SCOPE __declspec(dllimport)
#    endif
#  endif
#endif
#ifndef SDL_ROTOZOOM_SCOPE
#  define SDL_ROTOZOOM_SCOPE extern
#endif

	/* 

	Rotozoom functions

	*/

	SDL_ROTOZOOM_SCOPE SDL_Surface *rotozoomSurface(SDL_Surface * src, double angle, double zoom, int smooth);

	SDL_ROTOZOOM_SCOPE SDL_Surface *rotozoomSurfaceXY
		(SDL_Surface * src, double angle, double zoomx, double zoomy, int smooth);


	SDL_ROTOZOOM_SCOPE void rotozoomSurfaceSize(int width, int height, double angle, double zoom, int *dstwidth,
		int *dstheight);

	SDL_ROTOZOOM_SCOPE void rotozoomSurfaceSizeXY
		(int width, int height, double angle, double zoomx, double zoomy, 
		int *dstwidth, int *dstheight);

	/* 

	Zooming functions

	*/

	SDL_ROTOZOOM_SCOPE SDL_Surface *zoomSurface(SDL_Surface * src, double zoomx, double zoomy, int smooth);

	SDL_ROTOZOOM_SCOPE void zoomSurfaceSize(int width, int height, double zoomx, double zoomy, int *dstwidth, int *dstheight);

	/* 

	Shrinking functions

	*/     

	SDL_ROTOZOOM_SCOPE SDL_Surface *shrinkSurface(SDL_Surface * src, int factorx, int factory);

	/* 

	Specialized rotation functions

	*/

	SDL_ROTOZOOM_SCOPE SDL_Surface* rotateSurface90Degrees(SDL_Surface* src, int numClockwiseTurns);

	/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif				/* _SDL_rotozoom_h */

