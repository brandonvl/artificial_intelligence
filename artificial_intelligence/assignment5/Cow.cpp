#include "Cow.h"
#include "Game.h"
#include "Drawer.h"
#include "Rabbit.h"
#include "GameGeneticInstance.h"
#include "CowWanderState.h"

Cow::Cow(Game &game) : Vehicle(new Vector2D(350.0, 200.0), 10.0, new Vector2D(100.0,100.0),0.1,2.0,100.0,150.0,15.0, game)
{
	setDrawColor(0, 0, 0);
	makeMachine(game);
	respawn();
}

void Cow::makeMachine(Game &game) {
	_stateMachine = new StateMachine<Cow>(this, game);
	_stateMachine->changeState(&CowWanderState::instance());
}

bool Cow::handleMessage(const Telegram &msg) {
	return _stateMachine->handleMessage(msg);
}

void Cow::normalizeChancesTo100Scale() {

	int sum = _fleeChance + _seekPillChance + _hideChance + _seekWeaponChance;

	if (sum != 100) {
		_fleeChance = round(_fleeChance * 100 / sum);
		_seekPillChance = round(_seekPillChance * 100 / sum);
		_hideChance = round(_hideChance * 100 / sum);
		_seekWeaponChance = round(_seekWeaponChance * 100 / sum);
	}

}

void Cow::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	_stateMachine->update();

	Vehicle::update(game, time_elapsed);
}

void Cow::draw(Game &game) {
	std::string colorExtention = _geneticInstance->getColorExtention();
	game.getDrawer().drawSprite("cow" + colorExtention, getPos()->x, getPos()->y);
}

void Cow::respawn() {
	setPosition(_game->getCowSpawn());
}

Cow::~Cow()
{
}
