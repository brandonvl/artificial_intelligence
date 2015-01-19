#include "GameGeneticInstance.h"
#include "Cow.h"
#include "Rabbit.h"
#include "Pill.h"
#include "Weapon.h"
#include "Game.h"

GameGeneticInstance::GameGeneticInstance(Game &game, GameGeneticInstanceColor color)
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
	_rabbit = new Rabbit(game);
	_pill = new Pill();
	_weapon = new Weapon();

	// rework
	_cow->setGameGeneticInstance(*this);
	_rabbit->setGameGeneticInstance(*this);
	_pill->setGameGeneticInstance(*this);
	_weapon->setGameGeneticInstance(*this);
}

void GameGeneticInstance::update(Game &game, double time_elapsed) {

}

void GameGeneticInstance::draw(Game &game, double time_elapsed) {
	_cow->draw(game);
	_rabbit->draw(game);
	_weapon->draw(game);
	_pill->draw(game);
}


GameGeneticInstance::~GameGeneticInstance()
{
}
