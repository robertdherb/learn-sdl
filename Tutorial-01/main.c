#define SDL_MAIN_HANDLED
#define SCREEN_w 640
#define SCREEN_H 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "Prototype"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "SDL_video.h"

void game_init( void );
void game_quit( void );

static struct {
	/* Define Attributes */
		SDL_bool running;
		struct {
			unsigned int w;
			unsigned int h;
			const char *name;
			SDL_Window *window;
			SDL_Renderer *renderer;
		} screen;
	
	/* Define Methods */
		void (*init)(void);
		void (*quit)(void);

} Game = {
	SDL_FALSE,
	{
		SCREEN_SCALE*SCREEN_w,
		SCREEN_SCALE*SCREEN_H,
		SCREEN_NAME,
		NULL,
		NULL
	},
	game_init,
	game_quit
};


void
game_init( void )
{

	if( SDL_Init( SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS ) != 0 ){
		fprintf( stdout, "SDL failed to initialize, reason: %s\n", SDL_GetError() );
		exit( 101 );
	}

	unsigned int w = Game.screen.w;
	unsigned int h = Game.screen.h;
	const char *name = Game.screen.name;

	Game.screen.window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, 0
	);
	Game.screen.renderer = SDL_CreateRenderer(
		Game.screen.window, -1,
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);

	/*
	 * Maybe use SDL_CreateWindowAndRenderer() ?
	 */

	Game.running = SDL_TRUE;

}

void
game_quit( void )
{

	SDL_DestroyRenderer( Game.screen.renderer );
	SDL_DestroyWindow( Game.screen.window );

	Game.screen.window = NULL;
	Game.screen.renderer = NULL;

	SDL_Quit();

	Game.running = SDL_FALSE;

}


int
main( int argc, char *argv[] )
{

	SDL_Window * theWindow;

	Game.init();

	SDL_Event event;

	while( Game.running ) {
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_QUIT: 
					Game.running = SDL_FALSE;
				 	break;
			}
		}
		
		SDL_RenderClear( Game.screen.renderer );
		SDL_RenderPresent( Game.screen.renderer );
	}
	
	Game.quit();

	return 0;

}
