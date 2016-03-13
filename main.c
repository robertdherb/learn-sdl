#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include "SDL_video.h"

int
main( int argc, char *argv[] )
{

	SDL_Window * theWindow;

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ){
		fprintf( stdout, "SDL failed to initialize, reason: %s\n", SDL_GetError() );

		return 101;
	}

	theWindow = SDL_CreateWindow( "Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0 );
	
	SDL_Quit();

	return 0;

}
