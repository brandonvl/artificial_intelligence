#include "EntityManager.h"
#include "BaseGameEntity.h"

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::registerEntity(BaseGameEntity *entity)
{
	if (_entityMap.find(entity->getId()) == _entityMap.end())
		_entityMap.insert(std::make_pair(entity->getId(), entity));
}

BaseGameEntity *EntityManager::getEntityFromId(int id) const
{
	auto it = _entityMap.find(id);

	if (it != _entityMap.end())
		return it->second;
	else
		return nullptr;
}

void EntityManager::updateEntities(Game &game)
{
	for (auto it : _entityMap)
	{
		it.second->update(game,0.0);
	}
}

void EntityManager::removeEntity(BaseGameEntity *entity)
{
	if (_entityMap.find(entity->getId()) != _entityMap.end()) {
		_entityMap.erase(entity->getId());
		delete entity;
	}
}
