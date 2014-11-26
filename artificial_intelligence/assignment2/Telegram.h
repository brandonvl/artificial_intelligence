#pragma once
#include "MessageTypes.h"

struct Telegram
{
	int sender;
	int receiver;
	MessageType *msg;
	long long dispatchTime;
	void* extraInfo;

	Telegram(const int &sender, const int &receiver, MessageType &msg, const long long &distpatchTime, void *extraInfo = nullptr) : sender(sender), receiver(receiver), msg(&msg), dispatchTime(distpatchTime), extraInfo(extraInfo) {}
	bool operator<(const Telegram &other) const
	{
		return dispatchTime < other.dispatchTime;
	}
};