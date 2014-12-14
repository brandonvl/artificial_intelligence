#pragma once
#include "State.h"
#include <stack>

class Rabbit;
class Vertex;

class ChasePillRabbitState :
	public State<Rabbit>
{
private:
	ChasePillRabbitState();
	virtual ~ChasePillRabbitState();
	std::stack<Vertex*> _path;
	void clearPath();
public:


	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static ChasePillRabbitState &instance() {
		static ChasePillRabbitState _instance;
		return _instance;
	}
};

