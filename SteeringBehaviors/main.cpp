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

/////////////////////KEY CONTROLS///////////////////////////////////////
//
// 1- SEEK (change target with left click)
//
// 2- FLEE (change target with left click)
//
// 3- ARRIVE (change target with left click)
//
// 4- WANDER
//
// 5- PURSUIT
//
// 6- EVADE (NOT DONE)
//
// 7- FLEE / SEEK MIXTURE (change seek target with left click, flee target with right click)
//
////////////////////////////////////////////////////////////////////////


#include <SDL.h> 
#include <SDL_ttf.h>
#include "SteeringSprite.h"
#include "SteeringManager.h"
#include "Definitions.h"
#include "GameSeek.h"
#include "GameFlee.h"
#include "GameArrive.h"
#include "GameWander.h"
#include "GamePursuit.h"

#undef main

//TODO
//MAKE FORCE AND MAX SPEED CHANGEABLE WITH THE KEYS
//MAKE FORCE AND MAX SPEED CHANGE TO SOME DEFAULT VALUES EACH TIME YOU CHANGE SCENES
//MAKE AN EVADE SCENE
//CONGRATULATIONS, YOU HAVE FINISHED THE FIRST GROUP!!!
//MAKE A MIXTURE SEEK / FLEE WHERE LEFT CLICK PLACES THE SEEK POINT AND RIGHT CLICK PLACES THE FLEE POINT
//IMPLEMENT VECTOR PERP
//IMPLEMENT SET LOCAL ACCELERATION
//MAKE ARRIVE END ON TIP (TODO STEERING SPRITE.CPP)
//HAVE A HELP GAME STATE BY PRESSING ZERO WHERE IT TELLS WHICH SCENES ARE IN WHICH BUTTONS
//ALLOW SPRITES TO EACH HAVE THEIR OWN MAX SPEED
//MAKE ALL TARGETS IN STEERING SPRITE STD::VECTORS SO THEY CAN HAVE A BUNCH OF THEM
//MAKE SCENE WHERE YOU CLICK TO PLACE A FLEE TARGET BUT IT ONLY FLEES IF ITS WITHIN A CERTAIN DISTANCE AND YOU CAN PLACE A BUNCH


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		//TTF_Init();

		//TTF_Font* arial = TTF_OpenFont("arial.ttf", 20);
		//SDL_Color white = { 0, 0, 255, 255 };
		//SDL_Surface* textSurface = TTF_RenderText_Solid(arial, "HELP PAGE", white);
		//SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
		//SDL_Rect textRect;
		//textRect.x = textRect.y = 0;

		//SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

		//SDL_FreeSurface(textSurface);
		//textSurface = nullptr;

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
							GameSeek::getInstance()->sprite->setSeekTarget(Vector(event.button.x, event.button.y));
						if(GameFlee::getInstance()->sprite)
							GameFlee::getInstance()->sprite->setFleeTarget(Vector(event.button.x, event.button.y));
						if (GameArrive::getInstance()->sprite)
							GameArrive::getInstance()->sprite->setArriveTarget(Vector(event.button.x, event.button.y));
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
						case SDLK_5:
							m.changeState(GamePursuit::getInstance());
							break;
						}
					}
				}

				//SDL_RenderCopy(renderer, text, NULL, &textRect);
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
		//if (text)
		//{
		//	SDL_DestroyTexture(text);
		//}
	}
	SDL_Quit();
	return 0;
}