#include "GlobalCowState.h"
#include "Cow.h"
#include "MessageDispatcher.h"

GlobalCowState::GlobalCowState() : State<Cow>("GlobalCowState")
{
}


GlobalCowState::~GlobalCowState()
{
}

bool GlobalCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_RabbitPeeking:
		Dispatch.dispatchMessage(0.0, entity->getId(), msg.sender, MessageType::Msg_CowPresent, nullptr);
		return true;
	case MessageType::Msg_ChasingRabbitVisiting:
		Dispatch.dispatchMessage(0.0, entity->getId(), msg.sender, MessageType::Msg_CowCaught, nullptr);
		return true;
	}
	return false;
}

void GlobalCowState::enter(Cow *entity, Game &game)
{

}

void GlobalCowState::update(Cow *entity, Game &game)
{

}

void GlobalCowState::exit(Cow *entity, Game &game)
{

}
