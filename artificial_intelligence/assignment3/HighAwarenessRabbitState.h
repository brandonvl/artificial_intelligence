#pragma once
#include "State.h"
#include <set>
class Rabbit;

class HighAwarenessRabbitState :
	public State<Rabbit>
{
private:
	HighAwarenessRabbitState();
	virtual ~HighAwarenessRabbitState();
	bool _receivedChasingCowMessage = false;
	void doTeleport(Rabbit *entity, Game &game, std::set<int> *attempts);
public:
	virtual bool onMessage(Rabbit *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Rabbit *entity, Game &game) override;
	virtual void update(Rabbit *entity, Game &game) override;
	virtual void exit(Rabbit *entity, Game &game) override;

	static HighAwarenessRabbitState &instance() {
		static HighAwarenessRabbitState _instance;
		return _instance;
	}
};

