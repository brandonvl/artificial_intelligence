#pragma once

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;
class Pill;
class Weapon;
class Vehicle;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	Rabbit &getRabbit() { return *_rabbit; }
	Drawer &getDrawer()  { return *_drawer; }
	std::vector<Vehicle*> getCows() { return _cows; }

private:
	Drawer *_drawer;
	Vehicle *_testObject;
	std::vector<Vehicle*> _cows;
	Rabbit *_rabbit;
	void handleEvents();
	void update(const double &time_elapsed);
	void draw();
	bool _running = false, _gameOver = false;
};

