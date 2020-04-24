#pragma once
#include "enums.h"

struct Telegram
{
	int sender, receiver;

	MessageType message;

	double dispatchTime;

	void* extraInfo;

	Telegram(int _sender, int _receiver, MessageType _message) :
		sender(_sender), receiver(_receiver), message(_message), dispatchTime(0), extraInfo(nullptr)
	{

	}

	Telegram(int _sender, int _receiver, MessageType _message, double _dispatchTime) :
		sender(_sender), receiver(_receiver), message(_message), dispatchTime(_dispatchTime), extraInfo(nullptr)
	{

	}

	Telegram(int _sender, int _receiver, MessageType _message, void* _extraInfo) :
		sender(_sender), receiver(_receiver), message(_message), dispatchTime(0), extraInfo(_extraInfo)
	{

	}

	Telegram(int _sender, int _receiver, MessageType _message, double _dispatchTime, void* _extraInfo) :
		sender(_sender), receiver(_receiver), message(_message), dispatchTime(_dispatchTime), extraInfo(_extraInfo)
	{

	}

	bool operator<(const Telegram& t) const;
	bool operator==(const Telegram& t) const;
};