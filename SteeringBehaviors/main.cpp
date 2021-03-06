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
// 6- EVADE
//
// 7- FLEE / SEEK MIXTURE (change seek target with left click, flee target with right click)
//
// I GOT BORED AND STOPPED UPDATING THIS, JUST HIT RANDOM NUMBERS AND SEE WHAT HAPPENS, OR CHECK THE CODE
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
#include "GameEvade.h"
#include "GameSeekAndFlee.h"
#include "GameObstacleAvoidance.h"
#include "GameWallAvoidance.h"
#include "GameInterpose.h"
#include "GameHide.h"
#include "GamePathFollow.h"
#include "GameOffsetPursuit.h"

#undef main // this is a problem with SDL (and a great argument in favor of constexprs)

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
			SteeringManager& m = *SteeringManager::getInstance();
			m.setRenderer(renderer);
			
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
						//set the target for all of the game states sprites if we're in that instance
						if(m.isInState(GameSeek::getInstance()))
						   GameSeek::getInstance()->sprite->setSeekTarget(Vector(event.button.x, event.button.y));
						else if (m.isInState(GameFlee::getInstance()))
							GameFlee::getInstance()->sprite->setFleeTarget(Vector(event.button.x, event.button.y));
						else if (m.isInState(GameArrive::getInstance()))
							GameArrive::getInstance()->sprite->setArriveTarget(Vector(event.button.x, event.button.y));
						else if (m.isInState(GameOffsetPursuit::getInstance()))
							GameOffsetPursuit::getInstance()->sprite->setArriveTarget(Vector(event.button.x, event.button.y));
						else if (m.isInState(GameSeekAndFlee::getInstance()))
						{
							if(event.button.button == SDL_BUTTON_LEFT)
								GameSeekAndFlee::getInstance()->sprite->setSeekTarget(Vector(event.button.x, event.button.y));
							else if (event.button.button == SDL_BUTTON_RIGHT)
								GameSeekAndFlee::getInstance()->sprite->setFleeTarget(Vector(event.button.x, event.button.y));

						}

						//add a point to the path if we're following one
						else if (m.isInState(GamePathFollow::getInstance()))
						{
							GamePathFollow::getInstance()->path->addNode(Vector(event.button.x, event.button.y));
						}
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
						case SDLK_6:
							m.changeState(GameEvade::getInstance());
							break;
						case SDLK_7:
							m.changeState(GameSeekAndFlee::getInstance());
							break;
						case SDLK_8:
							m.changeState(GameObstacleAvoidance::getInstance());
							break;
						case SDLK_9:
							m.changeState(GameWallAvoidance::getInstance());
							break;
						case SDLK_0:
							m.changeState(GameInterpose::getInstance());
							break;
						case SDLK_q:
							m.changeState(GameHide::getInstance());
							break;
						case SDLK_w:
							m.changeState(GamePathFollow::getInstance());
							break;
						case SDLK_e:
							m.changeState(GameOffsetPursuit::getInstance());
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