#pragma once


class Game;

template<typename entity_type>
class State
{
	virtual void enter(entity_type *entity) = 0;
	virtual void update(entity_type *entity, Game &game) = 0;
	virtual void exit(entity_type *entity, Game &game) = 0;
};