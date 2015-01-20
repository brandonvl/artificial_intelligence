#pragma once


#include <string>

class Game;
class Cow;
class Rabbit;
class Pill;
class Weapon;

enum class GameGeneticInstanceColor { RED, BLUE, GREEN, YELLOW };

class GameGeneticInstance
{
private:
	Cow *_cow;
	Rabbit *_rabbit;
	Pill *_pill;
	Weapon *_weapon;
	std::string _colorExtension;
public:
	Rabbit &getRabbit() { return *_rabbit; }
	Cow &getCow() { return *_cow; }
	Pill &getPill() { return *_pill; }
	Weapon &getWeapon() { return *_weapon; }

	void respawnWeapon();
	void respawnPill();
	std::string &getColorExtention() { return _colorExtension; }
	GameGeneticInstance(Game &game, GameGeneticInstanceColor color);
	virtual void update(Game &game, double time_elapsed);
	virtual void draw(Game &game, double time_elapsed);
	virtual ~GameGeneticInstance();
};

