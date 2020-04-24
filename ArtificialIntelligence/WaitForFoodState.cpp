#include "WaitForFoodState.h"
#include "MessageDispatcher.h"
#include "enums.h"
#include "EatState.h"

using namespace std;

WaitForFoodState* WaitForFoodState::instance = nullptr;

void WaitForFoodState::enter(Fisherman* f)
{
	f->display("I'm gonna order a steak");

	//send a message to the chef (id 1) to cook him a steak
	Dispatcher->dispatchMessage(f->getId(), 1, MAKEMESTEAK);

	f->setLocation(RESTAURANT);
}

void WaitForFoodState::exit(Fisherman* f)
{
	f->display("this steak looks great");
}

void WaitForFoodState::execute(Fisherman* f)
{
	//just wait for the message
	f->display("I'm waiting for my steak");
}

//when we get a message that the steak is cooked, change state to eat state
bool WaitForFoodState::onMessage(Fisherman* f, const Telegram& msg)
{
	if (msg.message == STEAKREADY)
	{
		f->changeState(Eat);
		return true;
	}

	return false;
}
