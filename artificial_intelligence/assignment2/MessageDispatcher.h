#pragma once
#include <set>

struct Telegram;
class BaseGameEntity;
enum class MessageType;

class MessageDispatcher
{
private:
	std::set<Telegram> _priorityQ;

	void discharge(BaseGameEntity *receiver, const Telegram &msg);

	MessageDispatcher();
	MessageDispatcher(const MessageDispatcher&) {}
	MessageDispatcher &operator=(const MessageDispatcher&) {}
	virtual ~MessageDispatcher();

public:
	static MessageDispatcher& instance() {
		static MessageDispatcher _instance;
		return _instance;
	}

	void dispatchMessage(const long long &delay, const int &sender, const int &receiver, MessageType &msg, void *extraInfo);
	void dispatchDelayedMessages();
	#define Dispatch MessageDispatcher::instance()
};

