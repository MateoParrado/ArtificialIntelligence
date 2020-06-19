/////////////////////////////////////////////////////////////////////////
//							  SDL BASIC								   //
//																	   //
//				PROJECT TO SET UP AND TEST A SIMPLE SDL				   //
//						DISPLAY, AND MAKE A SPRITE					   //
//							  ARCHITECTURE							   //
//																	   //
//																	   //
//						DISPLAYS THREE SPRITES,      				   //
//						EACH MOVING DIFFERENTLY						   //
//																	   //
//																	   //
/////////////////////////////////////////////////////////////////////////

#include <SDL.h> 
#include "SimpleSprite.h"
#include "Definitions.h"
#undef main

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		SimpleSprite s(300, 300, .01, 1, 5);
		s.setVelocity(30, 0);

		SimpleSprite s1(100, 300, .01, 1, 5);
		s1.setAcceleration(0, 1);

		SimpleSprite s2(300, 100, .01, 1, 5);
		s2.setLocalVelocity(0.02, 0);

		if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;

			//we use this to store the first tick of each frame
			Uint32 startingTick;

			while (!done)
			{
				//get time since start of program
				startingTick = SDL_GetTicks();

				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				//draw sprites
				s.draw(renderer);
				s1.draw(renderer);
				s2.draw(renderer);

				//update sprites
				s1.update();
				s.update();
				s2.update();

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
				}
				
				SDL_RenderPresent(renderer);

				//used to maintain steady framerate
				if ((1000 / FPS) > SDL_GetTicks() - startingTick)
				{
					SDL_Delay((1000 / FPS) - (SDL_GetTicks() - startingTick));
				}
			}
		}

		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
		}
		if (window)
		{
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}