#pragma once
#include "State.h"
#include <stack>
class Cow;
class Vertex;
class ChaseCowState :
	public State<Cow>
{
private:
	ChaseCowState();
	virtual ~ChaseCowState();
public:
	

	virtual bool onMessage(Cow *entity, const Telegram &msg, Game &game) override;
	virtual void enter(Cow *entity, Game &game) override;
	virtual void update(Cow *entity, Game &game) override;
	virtual void exit(Cow *entity, Game &game) override;

	static ChaseCowState &instance() {
		static ChaseCowState _instance;
		return _instance;
	}
};

