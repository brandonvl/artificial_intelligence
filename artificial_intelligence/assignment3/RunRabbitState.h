#pragma once
#include "State.h"
#include <stack>

class Rabbit;
class Vertex;

class RunRabbitState :
	public State<Rabbit>
{
private:
	RunRabbitState();
	virtual ~RunRabbitState();
	bool _receivedChasingCowMessage;

	const int ACTION_RANGE = 2;

	bool lookAround(Rabbit *entity, Game &game);
	bool isNextToCow(Rabbit *entity, Game &game, int fieldKey);
	void run(Rabbit *entity, Game &game);
public:
	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static RunRabbitState &instance() {
		static RunRabbitState _instance;
		return _instance;
	}
};

