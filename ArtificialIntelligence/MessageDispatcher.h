#pragma once
#include <set>
#include "Telegram.h"
#include "Entity.h"

class MessageDispatcher
{
private:
	std::set<Telegram> queue;

	void discharge(Entity* receiver, const Telegram& msg);

	double startTime; //the time we start the program

	MessageDispatcher();
	MessageDispatcher(const MessageDispatcher&) = delete;
	MessageDispatcher& operator=(const MessageDispatcher&) = delete;

	static MessageDispatcher* instance;

public:
	static MessageDispatcher* getInstance()
	{
		if (!instance) instance = new MessageDispatcher();

		return instance;
	}

	void dispatchMessage(int sender, int receiver, MessageType msg);
	void dispatchMessage(int sender, int receiver, MessageType msg, double delay);
	void dispatchMessage(int sender, int receiver, MessageType msg, void* extraInfo);
	void dispatchMessage(int sender, int receiver, MessageType msg, double delay, void* extraInfo);

	void dispatchDelayedMessages();
};

#define Dispatcher MessageDispatcher::getInstance()
