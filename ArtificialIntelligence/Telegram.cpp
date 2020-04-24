#include "Telegram.h"

bool Telegram::operator<(const Telegram& t) const
{
	return dispatchTime < t.dispatchTime;
}

bool Telegram::operator==(const Telegram& t) const
{
	return (-0.25 < dispatchTime - t.dispatchTime) && (0.25 > dispatchTime - t.dispatchTime);
}
