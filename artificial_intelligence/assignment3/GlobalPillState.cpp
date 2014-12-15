#include "GlobalPillState.h"
#include "Pill.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Rabbit.h"
#include "EntityManager.h"
#include "Vertex.h"

GlobalPillState::GlobalPillState()
{
}


GlobalPillState::~GlobalPillState()
{
}

bool GlobalPillState::onMessage(Pill *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
		case MessageType::Msg_RabbitVisiting:
			Rabbit *rabbitEntity = static_cast<Rabbit*>(msg.extraInfo);
			if (!rabbitEntity->hasPill())
			{
				rabbitEntity->setPillUpgrade();
				Dispatch.dispatchMessage(0.0, entity->getId(), rabbitEntity->getId(), MessageType::Msg_PillUpgrade, nullptr);
				entity->getField()->removeData(*entity);
				entity->setField(nullptr);
				return true;
			}
			else
				return false;
		break;
	}

	return false;
}

void GlobalPillState::enter(Pill *entity, Game &game)
{

}

void GlobalPillState::update(Pill *entity, Game &game)
{

}

void GlobalPillState::exit(Pill *entity, Game &game)
{

}
