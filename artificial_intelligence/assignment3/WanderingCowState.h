#pragma once
#include "State.h"
class Cow;

class WanderingCowState :
	public State<Cow>
{
private:
	WanderingCowState();
	virtual ~WanderingCowState();
public:
	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	static WanderingCowState &instance() {
		static WanderingCowState _instance;
		return _instance;
	}
};

