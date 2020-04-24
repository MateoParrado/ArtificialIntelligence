#include "FishingState.h"
#include "Fisherman.h"
#include "SellState.h"
#include "WaitForFoodState.h"

using namespace std;

FishingState* FishingState::instance = nullptr;

void FishingState::enter(Fisherman* f)
{
	if (f->getLocation() != RIVER)
	{
		f->display("walking to the river to fish");

		f->setLocation(RIVER);
	}
}

void FishingState::exit(Fisherman* f)
{
	f->display("Leaving the river");
}

void FishingState::execute(Fisherman* f)
{
	f->fish++;

	f->display("I'm fishing for fish");
	f->display("I caught one!!");

	//should we go to the market?
	if (f->fish > 5)
	{
		f->display("I have a lot of fish, better sell them");
		f->changeState(Sell);
	}
	//should we go to the restaurant?
	else if (f->hunger > 10)
	{
		f->changeState(WaitForFood);
	}
}