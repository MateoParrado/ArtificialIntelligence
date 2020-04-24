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

		SimpleSprite s(300, 300);
		s.setVelocity(30, 0);
		SimpleSprite s1(100, 300);
		//s1.setAngularAcceleration(.000001);
		s1.setAcceleration(0, 0.0001);
		SimpleSprite s2(300, 100);
		//s2.setAngularVelocity(-0.0002);
		s2.setLocalVelocity(0.02, 0);

		if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;

			//we use this to store the first tick of each frame
			Uint32 startingTick;

			while (!done)
			{
				startingTick = SDL_GetTicks();

				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				s.draw(renderer);
				s1.draw(renderer);
				s2.draw(renderer);

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