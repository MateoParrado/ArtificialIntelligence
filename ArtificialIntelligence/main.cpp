/////////////////////////////////////////////////////////////////////////
//							  FISHERMAN MARTY						   //
//																	   //
//				PROJECT TO DEMONSTRATE A SIMPLE RELATIONSHIP   		   //
//					BETWEEN A FISHERMAN AND A CHEF					   //
//																	   //
//				 THE FISHERMAN AND CHEF BOTH GO ABOUT THEIR			   //
//				DAYS AS CONTROLLED BY A FINITE STATE MACHINE		   //
//				THEY SEND MESSAGES TO EACH OTHER WHEN NEEDED		   //
//						  TO CONVEY INSTRUCTIONS					   //
//																	   //
/////////////////////////////////////////////////////////////////////////

#include "Fisherman.h"
#include "Chef.h"
#include <thread>
#include <chrono>
#include "MessageDispatcher.h"

int main()
{
	Fisherman fisherman("Fisherman Marty");
	Chef chef("		Chef Boyardee");

	for (int i = 0; i < 20; i++)
	{
		//update entities
		fisherman.update();
		chef.update();

		//check for sent messages
		Dispatcher->dispatchDelayedMessages();

		//sleep for 250 ms
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	return 0;
}