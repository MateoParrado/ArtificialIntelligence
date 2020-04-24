#include "MessageDispatcher.h"
#include "EntityManager.h"
#include <ctime>

MessageDispatcher* MessageDispatcher::instance = nullptr;

MessageDispatcher::MessageDispatcher() :startTime(clock())
{

}

//send a message to an entity
void MessageDispatcher::discharge(Entity* receiver, const Telegram& msg)
{
	receiver->handleMessage(msg);
}

//public function used to tell class to send a message
void MessageDispatcher::dispatchMessage(int sender, int receiver, MessageType msg)
{
	Entity* rec = EntityMgr->getEntity(receiver);

	Telegram t(sender, receiver, msg);

	discharge(rec, t);
}

//this overload includes a message delay
void MessageDispatcher::dispatchMessage(int sender, int receiver, MessageType msg, double delay)
{
	Entity* rec = EntityMgr->getEntity(receiver);

	Telegram t(sender, receiver, msg, delay);

	if (delay <= 0)
	{
		discharge(rec, t);
	}
	else
	{
		double currTime = clock();
		t.dispatchTime = currTime + delay * CLOCKS_PER_SEC;

		queue.insert(t);
	}
}

//this overload includes a void* for any extra info needed along with the message
void MessageDispatcher::dispatchMessage(int sender, int receiver, MessageType msg, void* extraInfo)
{
	Entity* rec = EntityMgr->getEntity(receiver);

	Telegram t(sender, receiver, msg, extraInfo);

	discharge(rec, t);
}

//this overload includes both a delay and a void*
void MessageDispatcher::dispatchMessage(int sender, int receiver, MessageType msg, double delay, void* extraInfo)
{
	Entity* rec = EntityMgr->getEntity(receiver);

	Telegram t(sender, receiver, msg, delay, extraInfo);

	if (delay <= 0)
	{
		discharge(rec, t);
	}
	else
	{
		double currTime = clock();
		t.dispatchTime = currTime + delay * CLOCKS_PER_SEC;

		queue.insert(t);
	}
}

//called continuously, handles message timing
void MessageDispatcher::dispatchDelayedMessages()
{
	double currTime = clock();

	//check if we have passed the dispatch time for any messages
	while (queue.size() && queue.begin()->dispatchTime < currTime)
	{
		Telegram t = *queue.begin();

		Entity* rec = EntityMgr->getEntity(t.receiver);

		discharge(rec, t);

		queue.erase(queue.begin());
	}
}
