#pragma once


class Game;
struct Telegram;

template<typename entity_type>
class State
{
public:

	virtual bool onMessage(entity_type *entity, const Telegram &msg, Game &game) = 0;
	virtual void enter(entity_type *entity, Game &game) = 0;
	virtual void update(entity_type *entity, Game &game) = 0;
	virtual void exit(entity_type *entity, Game &game) = 0;

	virtual ~State() {}
};