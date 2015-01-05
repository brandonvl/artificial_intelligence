#pragma once

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;
class Pill;
class Weapon;

const int VERTEX_SIZE = 40;
const int VERTEX_MIDDLE = VERTEX_SIZE / 2;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	void gameOver() { _rabbit = nullptr; _gameOver = true; }
	Graph &getGraph() { return *_graph; }
	Rabbit &getRabbit() { return *_rabbit; }
	Drawer &getDrawer()  { return *_drawer; }
	Cow &getCow() { return *_cow; }
	Pill &getPill() { return *_pill; }
	Weapon &getWeapon() { return *_weapon; }

	void respawn(GameObject &gameObject);
private:
	void writeStatus();

	Graph *_graph;
	Drawer *_drawer;
	Cow *_cow;
	Rabbit *_rabbit;
	Pill *_pill;
	Weapon *_weapon;
	void handleEvents();
	void update();
	void draw();
	bool _running = false, _gameOver = false;
	bool doTurn = false;
};

