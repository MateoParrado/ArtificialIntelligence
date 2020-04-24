#include "EatState.h"
#include "SellState.h"
#include "Fisherman.h"
#include "FishingState.h"

using namespace std;

EatState* EatState::instance = nullptr;

void EatState::enter(Fisherman* f)
{
	f->display("I'm hungry, I'm gonna go eat");
}

void EatState::exit(Fisherman* f)
{
	f->display("That was good food!");
}

void EatState::execute(Fisherman* f)
{
	f->display("I'm eating some nice steak");
	
	f->money -= 2;
	f->hunger = 0;

	f->changeState(Fish); 
}