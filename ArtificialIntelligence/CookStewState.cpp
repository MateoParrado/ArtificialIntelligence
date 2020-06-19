#include "CookStewState.h"
#include "CookSteakState.h"
#include "Chef.h"
#include "MessageDispatcher.h"
#include "enums.h"

using namespace std;

CookStewState* CookStewState::instance = nullptr;

void CookStewState::enter(Chef* c)
{
	c->display("I'm gonna cook some stew");

}

void CookStewState::exit(Chef* c)
{
	c->display("That came out nice, time to serve it");
}

void CookStewState::execute(Chef* c)
{
	c->display("This smells good");

	c->changeState(CookStew);
}

//we cook stew continuously until someone orders steak
bool CookStewState::onMessage(Chef* c, const Telegram& msg)
{
	if (msg.message == MessageType::MAKEMESTEAK)
	{
		c->changeState(CookSteak);

		//send a message to self in 0.5 seconds that the steak is ready (to account for cooking time)
		Dispatcher->dispatchMessage(c->getId(), c->getId(), MessageType::STEAKREADY, 0.5);
		return true;
	}

	return false;
}
