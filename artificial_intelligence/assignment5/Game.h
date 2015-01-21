#pragma once

#include "2D\Vector2D.h"
#include "SDL.h"

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;
class Pill;
class Weapon;
class Vehicle;

#include "GameGeneticInstance.h"

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	//Rabbit &getRabbit() { return *_rabbit; }
	Drawer &getDrawer()  { return *_drawer; }
	//Cow &getCow() { return *_cow; }
	Vector2D getCowSpawn() { return Vector2D(200, 350); }
	Vector2D getRabbitSpawn() { return Vector2D(600, 350); }
	void respawnRandom(Vehicle *objectToRespawn, int xStart = 0, int xEnd = 800, int yStart = 0, int yEnd = 800);
private:
	int _rounds = 0;
	Uint32 _startTimeStamp = -1;
	void startRound();
	bool isRoundFinished();
	void applyGeneticAlgorithm();
	std::vector<GameGeneticInstance*> _geneticInstances;
	void showChances(Cow &cow);
	Drawer *_drawer;
	void loadInstanceColorImages();
	void handleEvents();
	void update(const double &time_elapsed);
	void draw();
	bool _running = false, _gameOver = false;
};

