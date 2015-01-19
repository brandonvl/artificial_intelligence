#include "Weapon.h"
#include "GameGeneticInstance.h"
#include "Game.h"
#include "Drawer.h"


Weapon::Weapon() : Vehicle(new Vector2D(600.0, 400.0), 10.0, new Vector2D(0.0, 0.0), 0.1, 2.0, 150.0, 150.0, 15.0)
{
}


Weapon::~Weapon()
{
}

void Weapon::update(Game &game, const double &time_elapsed) {

	//update the time elapsed
	_time_elapsed = time_elapsed;

	//_stateMachine->update();

	//Vehicle::update(game, time_elapsed);
}

void Weapon::draw(Game &game) {
	std::string colorExtendtion = _gameGeneticInstance->getColorExtention();
	game.getDrawer().drawSprite("weapon" + colorExtendtion, getPos()->x, getPos()->y);
}
