#include "FishermanGlobalState.h"
#include "DrinkState.h"

FishermanGlobalState* FishermanGlobalState::instance = nullptr;

void FishermanGlobalState::enter(Fisherman* f)
{
	return;
}

void FishermanGlobalState::exit(Fisherman* f)
{
	return;
}

void FishermanGlobalState::execute(Fisherman* f)
{
	if (f->thirst > 15)
	{
		f->thirst = 0;
		f->changeState(Drink);
	}
}