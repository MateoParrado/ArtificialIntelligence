#include "Telegram.h"

//used for sorting in a set, sort by dispatch time
bool Telegram::operator<(const Telegram& t) const
{
	return dispatchTime < t.dispatchTime;
}

//used to remove duplicates in a set, two time stamps are the same if they are within 0.25 of each other
bool Telegram::operator==(const Telegram& t) const
{
	return  t.message == message &&
			t.sender == sender &&
			t.receiver == receiver &&
		    (-0.25 < dispatchTime - t.dispatchTime) 
		    && (0.25 > dispatchTime - t.dispatchTime);
}
