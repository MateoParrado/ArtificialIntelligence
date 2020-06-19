#include "SellState.h"
#include "Fisherman.h"
#include "FishingState.h"

using namespace std;

SellState* SellState::instance = nullptr;

void SellState::enter(Fisherman* f)
{
	f->display("going to the market to sell my fish");

	f->setLocation(Location::MARKET);
}

void SellState::exit(Fisherman* f)
{
	f->display("Leaving the market");
}

//sell the fish, gain money, and lose all the fish
void SellState::execute(Fisherman* f)
{
	f->display("Selling my fish at the market!");
	f->display("I sold them all, time to go back to fishing");

	f->money += f->fish;
	f->fish = 0;

	f->changeState(Fish);
}