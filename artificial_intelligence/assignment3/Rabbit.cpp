#include "Rabbit.h"
#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "GlobalRabbitState.h"
#include "WanderingRabbitState.h"

Rabbit::~Rabbit()
{
	getField()->removeData(*this);
	delete _stateMachine;
}

void Rabbit::makeMachine(Game &game)
{
	_stateMachine = new StateMachine<Rabbit>(this, game);
	_stateMachine->setGlobalState(&GlobalRabbitState::instance());
	_stateMachine->changeState(&WanderingRabbitState::instance());
}


void Rabbit::update(Game &game)
{
	if (_stateMachine)
		_stateMachine->update();
}

bool Rabbit::handleMessage(const Telegram &msg)
{
	if (_stateMachine) {
		return _stateMachine->handleMessage(msg);
	}
	else
		return false;
}

void Rabbit::updateRunChance(bool success) {
	_runChance += success ? CHANCE_SCALE_FACTOR : -CHANCE_SCALE_FACTOR;
	validateChances();
}

void Rabbit::updateSearchWeaponChance(bool success) {
	_searchWeaponChance += success ? CHANCE_SCALE_FACTOR : -CHANCE_SCALE_FACTOR;
	validateChances();
}

void Rabbit::updateSearchPillChance(bool success) {
	_searchPillChance += success ? CHANCE_SCALE_FACTOR : -CHANCE_SCALE_FACTOR;
	validateChances();
}

// checks (and corrects) chance bounds
void Rabbit::validateChances() {

	// Check for minimum bounds
  	if (_runChance < CHANCE_BOUNDS_MIN)
		_runChance = CHANCE_BOUNDS_MIN;

	if (_searchWeaponChance < CHANCE_BOUNDS_MIN)
		_searchWeaponChance = CHANCE_BOUNDS_MIN;

	if (_searchPillChance < CHANCE_BOUNDS_MIN)
		_searchPillChance = CHANCE_BOUNDS_MIN;

	// Check for maximum bounds
	if (_runChance > CHANCE_BOUNDS_MAX)
		_searchWeaponChance = CHANCE_BOUNDS_MAX;

	if (_searchWeaponChance > CHANCE_BOUNDS_MAX)
		_searchWeaponChance = CHANCE_BOUNDS_MAX;

	if (_searchPillChance > CHANCE_BOUNDS_MAX)
		_searchPillChance = CHANCE_BOUNDS_MAX;

	printf("Chances are ajusted (run: %d, searchWeapon: %d, searchPill: %d)", _runChance, _searchWeaponChance, _searchPillChance); 
}