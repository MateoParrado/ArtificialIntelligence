/////////////////////////////////////////////////////////////////////////
//					     STEERING BEHAVIORS							   //
//																	   //
//				PROJECT TO DEMONSTRATE A VARIETY OF SIMPLE   		   //
//					STEERING BEHAVIORS ON SPRITES					   //
//																	   //
//				NUMBER KEYS CHANGE THE CURRENT BEHAVIOR      		   //
//				MOUSE CLICKS CHANGE THE TARGET POSITION				   //
//																	   //
//																	   //
//																	   //
//																	   //
/////////////////////////////////////////////////////////////////////////


#include <SDL.h> 
#include "SteeringSprite.h"
#include "SteeringManager.h"
#include "Definitions.h"
#include "GameSeek.h"
#include "GameFlee.h"
#include "GameArrive.h"
#include "GameWander.h"

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
			//this is the game controller, it handles the displaying and updating of the correct group of sprites in the right steering behavior
			SteeringManager m(renderer);
			
			SDL_bool done = SDL_FALSE;

			//we use this to store the first tick of each frame
			Uint32 startingTick;

			while (!done)
			{
				//get milliseconds since program start
				startingTick = SDL_GetTicks();

				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				//update and draw current game state
				m.update();

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
					else if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						//set the target for all of the game states sprites, but only if they've been initialized
						if(GameSeek::getInstance()->sprite)
							GameSeek::getInstance()->sprite->setTarget(Vector(event.button.x, event.button.y));
						if(GameFlee::getInstance()->sprite)
							GameFlee::getInstance()->sprite->setTarget(Vector(event.button.x, event.button.y));
						if (GameArrive::getInstance()->sprite)
							GameArrive::getInstance()->sprite->setTarget(Vector(event.button.x, event.button.y));
					}
					else if (event.type == SDL_KEYDOWN)
					{
						//change gamestate on number key press
						switch (event.key.keysym.sym)
						{
						case SDLK_1:
							m.changeState(GameSeek::getInstance());
							break;
						case SDLK_2:
							m.changeState(GameFlee::getInstance());
							break;
						case SDLK_3:
							m.changeState(GameArrive::getInstance());
							break;
						case SDLK_4:
							m.changeState(GameWander::getInstance());
							break;
						}
					}
				}

				SDL_RenderPresent(renderer);

				//to cap the framerate
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