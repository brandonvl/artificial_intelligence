#include "GlobalWeaponState.h"
#include "Weapon.h"
#include "Rabbit.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"

GlobalWeaponState::GlobalWeaponState()
{
}


GlobalWeaponState::~GlobalWeaponState()
{
}

bool GlobalWeaponState::onMessage(Weapon *entity, const Telegram &msg, Game &game)
{
	switch (msg.msg)
	{
	case MessageType::Msg_RabbitVisiting:
		Rabbit *rabbitEntity = static_cast<Rabbit*>(msg.extraInfo);
		if (!rabbitEntity->hasWeapon())
		{
			rabbitEntity->setWeapon();
			Dispatch.dispatchMessage(0.0, entity->getId(), rabbitEntity->getId(), MessageType::Msg_WeaponUpgrade, nullptr);
			EntityMgr.removeEntity(entity);
			return true;
		}
		else
			return false;
		break;
	}

	return false;
}

void GlobalWeaponState::enter(Weapon *entity, Game &game)
{

}

void GlobalWeaponState::update(Weapon *entity, Game &game)
{

}

void GlobalWeaponState::exit(Weapon *entity, Game &game)
{

}