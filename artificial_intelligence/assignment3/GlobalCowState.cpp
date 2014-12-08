#include "GlobalCowState.h"
#include "Cow.h"

GlobalCowState::GlobalCowState()
{
}


GlobalCowState::~GlobalCowState()
{
}

bool GlobalCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	return false;
}

void GlobalCowState::enter(Cow *entity, Game &game)
{

}

void GlobalCowState::update(Cow *entity, Game &game)
{

}

void GlobalCowState::exit(Cow *entity, Game &game)
{

}
