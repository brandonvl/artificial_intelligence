#pragma once
#include <map>

class BaseGameEntity;
class Game;

class EntityManager
{
private:
	EntityManager();
	EntityManager(const EntityManager&) {}
	EntityManager &operator=(const EntityManager&) {}
	virtual ~EntityManager();

	typedef std::map<int, BaseGameEntity*> EntityMap;

	EntityMap _entityMap;

public:
	static EntityManager& instance() {
		static EntityManager _instance;
		return _instance;
	}

	void updateEntities(Game &game);
	void registerEntity(BaseGameEntity *entity);
	BaseGameEntity *getEntityFromId(int id) const;
	void removeEntity(BaseGameEntity *entity);
	#define EntityMgr EntityManager::instance()
};

