#include "GlobalRabbitState.h"
#include "Rabbit.h"
#include "Telegram.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "Cow.h"
#include "WanderingRabbitState.h"
#include "ChaseCowRabbitState.h"
#include "Game.h"
#include "Pill.h"

GlobalRabbitState::GlobalRabbitState() : State<Rabbit>("GlobalRabbitState")
{
}


GlobalRabbitState::~GlobalRabbitState()
{
}

bool GlobalRabbitState::onMessage(Rabbit *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_ChasingCowVisiting:
		if (entity->hasPill()) {
			std::cout << "The cow caught the rabbit, but rabbit has pill. Cow is going to sleep." << std::endl;
			Dispatch.dispatchMessage(0.0, entity->getId(), static_cast<Cow*>(msg.extraInfo)->getId(), MessageType::Msg_CowSleep, nullptr);

			game.respawn(game.getPill());
			entity->setPillUpgrade(false);
			entity->updateSearchPillChance(true);
			return true;
		}
		else {
			std::cout << "The cow caught the rabbit!" << std::endl;
			Dispatch.dispatchMessage(0.0, entity->getId(), static_cast<Cow*>(msg.extraInfo)->getId(), MessageType::Msg_RabbitCaught, nullptr);
			
			game.respawn(*entity);
		}
		return false;
	case MessageType::Msg_PillUpgrade:
		std::cout << "Pill replied, Rabbit now has pill! Lets wander" << std::endl;
		entity->changeState(&WanderingRabbitState::instance());
		return true;
	case MessageType::Msg_WeaponUpgrade:
		std::cout << "Weapon replied, Rabbit now has weapon! Lets chase the damn cow" << std::endl;
		entity->changeState(&ChaseCowRabbitState::instance());
		return true;
	}

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
