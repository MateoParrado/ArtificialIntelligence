#pragma once
#include <set>
#include "Telegram.h"
#include "Entity.h"

//class used to control the sending and receiving of all messages
class MessageDispatcher
{
private:
	//used for timed messages
	std::set<Telegram> queue;

	//private function to deliver a message
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

	//public function used to tell this class we need a message sent
	//four constructors allow us to choose wether or not we need delay and extraInfo
	void dispatchMessage(int sender, int receiver, MessageType msg);
	void dispatchMessage(int sender, int receiver, MessageType msg, double delay);
	void dispatchMessage(int sender, int receiver, MessageType msg, void* extraInfo);
	void dispatchMessage(int sender, int receiver, MessageType msg, double delay, void* extraInfo);

	//called continuously to handle timed messages
	void dispatchDelayedMessages();
};

#define Dispatcher MessageDispatcher::getInstance()
