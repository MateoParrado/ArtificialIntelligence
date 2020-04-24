#pragma once
#include "enums.h"

//basic message class used to transfer between different entities
struct Telegram
{
	int sender, receiver;

	MessageType message;

	//how long should we wait before sending the message?
	double dispatchTime;

	//used to transfer whatever extra info might be needed with the message
	void* extraInfo;

	//these four constructors allow you to decide wether to use or not use dispatch time and extra info
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

	//used for set sorting
	bool operator<(const Telegram& t) const;
	bool operator==(const Telegram& t) const;
};