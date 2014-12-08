#pragma once
#include "State.h"
class Cow;

class GlobalCowState : public State<Cow>
{
private:
	GlobalCowState();
	virtual ~GlobalCowState();
public:
	

	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	static GlobalCowState &instance() {
		static GlobalCowState _instance;
		return _instance;
	}
};

