#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "Telegram.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include <chrono>
#include <ctime>

MessageDispatcher::MessageDispatcher()
{
}


MessageDispatcher::~MessageDispatcher()
{
}

void MessageDispatcher::discharge(BaseGameEntity *receiver, const Telegram &msg)
{

}

void MessageDispatcher::dispatchMessage(const long long &delay, const int &sender, const int &receiver, MessageType &msg, void *extraInfo)
{
	BaseGameEntity *receiveEntity = EntityMgr.getEntityFromId(receiver);

	Telegram telegram{ sender, receiver, msg, 0, extraInfo };

	if (delay <= 0.0)
	{
		discharge(receiveEntity, telegram);
	}
	else
	{
		auto currentTime = std::chrono::seconds(std::time(nullptr));

		telegram.dispatchTime = currentTime.count() + delay;

		_priorityQ.insert(telegram);
	}
}

void MessageDispatcher::dispatchDelayedMessages()
{

}
