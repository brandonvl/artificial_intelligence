#pragma once
#include "State.h"
#include <stack>

class Rabbit;
class Vertex;

class ChaseCowRabbitState :
	public State<Rabbit>
{
private:
	ChaseCowRabbitState();
	virtual ~ChaseCowRabbitState();

	bool _receivedCowCaughtMessage = false;
public:


	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static ChaseCowRabbitState &instance() {
		static ChaseCowRabbitState _instance;
		return _instance;
	}
};

