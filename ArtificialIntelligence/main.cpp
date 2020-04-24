#include "Fisherman.h"
#include "Chef.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include "MessageDispatcher.h"
#include "Vector.h"

int main()
{
	Vector p;

	p.zero();

	Fisherman fisherman("Fisherman Marty");
	Chef chef("		Chef Boyardee");

	for (int i = 0; i < 20; i++)
	{
		fisherman.update();
		chef.update();
		Dispatcher->dispatchDelayedMessages();

		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	return 0;
}