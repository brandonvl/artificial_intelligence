#include "GlobalRabbitState.h"
#include "Rabbit.h"
#include "Telegram.h"
#include "MessageTypes.h"

GlobalRabbitState::GlobalRabbitState()
{
}


GlobalRabbitState::~GlobalRabbitState()
{
}

bool GlobalRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	return false;
}

void GlobalRabbitState::enter(Rabbit *entity, Game &game)
{

}

void GlobalRabbitState::update(Rabbit *entity, Game &game)
{

}

void GlobalRabbitState::exit(Rabbit *entity, Game &game)
{

}
