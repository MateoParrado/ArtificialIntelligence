#include "CookSteakState.h"
#include "Chef.h"
#include "MessageDispatcher.h"
#include "CookStewState.h"

using namespace std;

CookSteakState* CookSteakState::instance = nullptr;

void CookSteakState::enter(Chef* c)
{
	c->display("I just got an order for steak");

}

void CookSteakState::exit(Chef* c)
{
	c->display("That steak looked good");
}

void CookSteakState::execute(Chef* c)
{
	c->display("This steak isn't done yet");

}

//the message received here should be sent by the chef himself
//sends a message to the fisherman if the steak is done
bool CookSteakState::onMessage(Chef* c, const Telegram& msg)
{
	if (msg.message == MessageType::STEAKREADY)
	{
		//id 0 is the fisherman
		Dispatcher->dispatchMessage(c->getId(), 0, MessageType::STEAKREADY);

		//go back to cooking stew
		c->changeState(CookStew);
		return true;
	}

	return false;
}
