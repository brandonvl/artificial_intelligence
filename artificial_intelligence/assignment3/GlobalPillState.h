#pragma once
#include "State.h"
class Pill;

class GlobalPillState :
	public State<Pill>
{
private:
	GlobalPillState();
	virtual ~GlobalPillState();

public:
	

	virtual bool onMessage(Pill *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Pill *entity, Game &game) override;
	virtual void update(Pill *entity, Game &game) override;
	virtual void exit(Pill *entity, Game &game) override;

	static GlobalPillState &instance() {
		static GlobalPillState _instance;
		return _instance;
	}
};

