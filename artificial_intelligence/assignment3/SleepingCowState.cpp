#include "SleepingCowState.h"
#include "ChaseCowState.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"
#include "Cow.h"
#include <set>
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Drawer.h"
#include <iostream>
//#include "ChasePillCowState.h"

SleepingCowState::SleepingCowState()
{
}


SleepingCowState::~SleepingCowState()
{
}

bool SleepingCowState::onMessage(Cow *entity, const Telegram &msg, Game &game)
{
	return false;
}

void SleepingCowState::enter(Cow *entity, Game &game)
{
	game.getDrawer().setColorOverLay(entity->getName(), 0, 255, 0);
	_sleepCounter = 5;
}

void SleepingCowState::update(Cow *entity, Game &game)
{
	if (--_sleepCounter <= 0) {
		entity->changeState(&ChaseCowState::instance());
	}
}

void SleepingCowState::exit(Cow *entity, Game &game)
{

}
