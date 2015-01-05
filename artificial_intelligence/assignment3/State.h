#pragma once
#include <string>

class Game;
struct Telegram;

template<typename entity_type>
class State
{
protected:
	const std::string _name;

public:

	virtual bool onMessage(entity_type *entity, const Telegram &msg, Game &game) = 0;
	virtual void enter(entity_type *entity, Game &game) = 0;
	virtual void update(entity_type *entity, Game &game) = 0;
	virtual void exit(entity_type *entity, Game &game) = 0;

	const std::string getName() const { return _name; }

	State(std::string name) : _name(name) {}
	virtual ~State() {}
};