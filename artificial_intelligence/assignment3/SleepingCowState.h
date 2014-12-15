#pragma once
#include "State.h"
class Cow;

class SleepingCowState :
	public State<Cow>
{
private:
	SleepingCowState();
	virtual ~SleepingCowState();
	int _sleepCounter = 5;

public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	static SleepingCowState &instance() {
		static SleepingCowState _instance;
		return _instance;
	}
};

