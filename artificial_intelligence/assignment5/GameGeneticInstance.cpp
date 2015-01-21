#include "GameGeneticInstance.h"
#include "Cow.h"
#include "Rabbit.h"
#include "Pill.h"
#include "Weapon.h"
#include "Game.h"
#include "EntityManager.h"

GameGeneticInstance::GameGeneticInstance(Game &game, GameGeneticInstanceColor color, int hideChance, int seekPillChance, int seekWeaponChance, int fleeChance)
{
	switch (color)
	{
		case GameGeneticInstanceColor::RED:
			_colorExtension = "Red";
			break;
		case GameGeneticInstanceColor::BLUE:
			_colorExtension = "Blue";
			break;
		case GameGeneticInstanceColor::GREEN:
			_colorExtension = "Green";
			break;
		case GameGeneticInstanceColor::YELLOW:
			_colorExtension = "Yellow";
			break;
	}

	_cow = new Cow(game);
	_cow->setChances(hideChance, seekPillChance, seekWeaponChance, fleeChance);
	_rabbit = new Rabbit(game);
	_pill = new Pill(game);
	_weapon = new Weapon(game);

	EntityMgr.registerEntity(_cow);
	EntityMgr.registerEntity(_rabbit);
	EntityMgr.registerEntity(_pill);
	EntityMgr.registerEntity(_weapon);

	_cow->setGeneticInstance(*this);
	_rabbit->setGeneticInstance(*this);
	_pill->setGeneticInstance(*this);
	_weapon->setGeneticInstance(*this);

	_cow->normalizeChancesTo100Scale();

	_pill->respawn();
	_weapon->respawn();
}

void GameGeneticInstance::respawnWeapon() {
	_weapon->respawn();
}

void GameGeneticInstance::respawnPill() {
	_pill->respawn();
}

void GameGeneticInstance::update(Game &game, double time_elapsed) {
	_cow->update(game, time_elapsed);
	_rabbit->update(game, time_elapsed);
}

void GameGeneticInstance::draw(Game &game, double time_elapsed) {
	_cow->draw(game);
	_rabbit->draw(game);
	_weapon->draw(game);
	_pill->draw(game);
}


GameGeneticInstance::~GameGeneticInstance()
{
	delete _pill;
	delete _weapon;
	delete _cow;
	delete _rabbit;
}
