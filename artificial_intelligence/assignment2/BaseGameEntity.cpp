#include "BaseGameEntity.h"

int BaseGameEntity::_nextValidId = 0;

void BaseGameEntity::setID(int id) {
	if (id >= BaseGameEntity::_nextValidId) {
		_id = id;
		BaseGameEntity::_nextValidId = id + 1;
	}
}