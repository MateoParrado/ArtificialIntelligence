#include <SDL.h> 
#include "SteeringSprite.h"
#include "SteeringManager.h"
#include "Definitions.h"
#include "GameSeek.h"

#undef main

//TODO
//SET THE FRAMERATE AT 30 FPS SO I DONT NEED TO USE THESE RIDICULOUSLY SMALL NUMEBRS ANYMORE

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;


		if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0)
		{
			SteeringManager m(renderer);
			
			SDL_bool done = SDL_FALSE;

			//we use this to store the first tick of each frame
			Uint32 startingTick;

			while (!done)
			{
				startingTick = SDL_GetTicks();

				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				m.update();

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
					else if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						GameSeek::getInstance()->sprite->setTarget(Vector(event.button.x, event.button.y));
					}
				}

				SDL_RenderPresent(renderer);

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