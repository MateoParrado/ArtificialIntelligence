#pragma once
#include "State.h"
#include "Telegram.h"

//the state machine used to implement every state change and every game controller
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
		//call exit of current state
		if(currState) currState->exit(owner);

		//call enter of new state
		s->enter(owner);

		//save previous state for state reversions
		prevState = currState;

		currState = s;
	}

	//go back to previous state
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
		if (globState && globState->onMessage(owner, msg))
		{
			return true;
		}

		//none of our states can handle it
		return false;
	}

	//getters
	State<T>* currentState() const { return currState; }
	State<T>* globalState() const { return globState; }
	State<T>* previousState() const { return prevState; }

	//returns true if we are currently in state s
	bool isInState(const State<T>& s) const
	{
		return s.currentState() == this->currentState();
	}
};