#include "FishermanGlobalState.h"
#include "DrinkState.h"

FishermanGlobalState* FishermanGlobalState::instance = nullptr;

//enter and exit do nothing because this state is never not active so they are never called
void FishermanGlobalState::enter(Fisherman* f)
{
	return;
}

void FishermanGlobalState::exit(Fisherman* f)
{
	return;
}

//if we are thirsty stop what we are doing and drink
void FishermanGlobalState::execute(Fisherman* f)
{
	if (f->thirst > 15)
	{
		f->thirst = 0;
		f->changeState(Drink);
	}
}