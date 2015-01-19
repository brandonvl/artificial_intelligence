#pragma once

#include "2D\Vector2D.h"

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;
class Pill;
class Weapon;
class Vehicle;
class GameGeneticInstance;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	Rabbit &getRabbit() { return *_rabbit; }
	Drawer &getDrawer()  { return *_drawer; }
	Cow &getCow() { return *_cow; }
	Vector2D getCowSpawn() { return Vector2D(350, 200); }
	Vector2D getRabbitSpawn() { return Vector2D(350, 600); }

private:
	std::vector<GameGeneticInstance*> _geneticInstances;
	GameGeneticInstance *_geneticInstance;
	Drawer *_drawer;
	Cow *_cow; // legacy
	Rabbit *_rabbit; // legacy
	void loadInstanceColorImages();
	void handleEvents();
	void update(const double &time_elapsed);
	void draw();
	bool _running = false, _gameOver = false;
};

