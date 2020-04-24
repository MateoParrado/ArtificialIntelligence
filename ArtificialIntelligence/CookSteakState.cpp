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
	//c->revertState();
}

void CookSteakState::execute(Chef* c)
{
	c->display("This steak isn't done yet");

}

bool CookSteakState::onMessage(Chef* c, const Telegram& msg)
{
	if (msg.message == STEAKREADY)
	{
		Dispatcher->dispatchMessage(c->getId(), 0, STEAKREADY);
		c->changeState(CookStew);
		return true;
	}

	return false;
}
