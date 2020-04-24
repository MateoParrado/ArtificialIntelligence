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

bool CookStewState::onMessage(Chef* c, const Telegram& msg)
{
	if (msg.message == MAKEMESTEAK)
	{
		c->changeState(CookSteak);
		Dispatcher->dispatchMessage(c->getId(), c->getId(), STEAKREADY, 0.5);
		return true;
	}

	return false;
}
