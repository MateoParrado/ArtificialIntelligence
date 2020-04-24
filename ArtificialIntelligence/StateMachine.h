#pragma once
#include "State.h"
#include "Telegram.h"

template<class T>
class StateMachine
{
private:
	//pointer to owner
	T* owner;

	State<T>* currState;
	State<T>* prevState;
	State<T>* globState;

public:
	StateMachine(T* _owner) : owner(_owner), currState(nullptr), prevState(nullptr), globState(nullptr)
	{

	}

	//used to initialize only
	void setCurrState(State<T>* s) { currState = s; };
	void setPrevState(State<T>* s) { prevState = s; };
	void setGlobState(State<T>* s) { globState = s; };

	void update() const
	{
		if (globState) globState->execute(owner);

		if (currState) currState->execute(owner);
	}

	void changeState(State<T>* s)
	{
		if(currState) currState->exit(owner);

		s->enter(owner);

		prevState = currState;
		currState = s;
	}

	void revertState()
	{
		changeState(prevState);
	}

	bool handleMessage(const Telegram& msg)
	{
		//if we have a current state and it gets handled
		if (currState && currState->onMessage(owner, msg))
		{
			return true;
		}

		//if we have a global state, and it doesnt get handled above, and global state handles it
		else if (globState && globState->onMessage(owner, msg))
		{
			return true;
		}

		return false;
	}

	//getters
	State<T>* currentState() const { return currState; }
	State<T>* globalState() const { return globState; }
	State<T>* previousState() const { return prevState; }

	bool isInState(const State<T>& s) const
	{
		return s.currentState() == this->currentState();
	}
};