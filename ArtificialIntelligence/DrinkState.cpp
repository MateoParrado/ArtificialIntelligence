#include "DrinkState.h"
#include "Fisherman.h"

using namespace std;

DrinkState* DrinkState::instance = nullptr;

void DrinkState::enter(Fisherman* f)
{
	f->display("Hmm, I'm kinda thirsty");
}

void DrinkState::exit(Fisherman* f)
{
	f->display("That was refreshing!");
}

void DrinkState::execute(Fisherman* f)
{
	switch (f->getLocation())
	{
	case RIVER:
		f->display("I'm gonna drink some refreshing water");
		break;
	case MARKET:
		f->display("I'm gonna buy a soda");
		f->money -= 1;
		break;
	case RESTAURANT:
		f->display("I'll order a glass of water");
		break;
	}

	f->revertState();
}