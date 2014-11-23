#pragma once

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	Graph &getGraph() { return *_graph; }
	Rabbit &getRabbit() { return *_rabbit; }
private:
	std::vector<GameObject*> _gameObjects;
	Graph *_graph;
	Drawer *_drawer;
	Cow *_cow;
	Rabbit *_rabbit;
	void handleEvents();
	void update();
	void draw();
	bool _running = false;
	const int VERTEX_SIZE = 50;
	const int VERTEX_MIDDLE = VERTEX_SIZE / 2;
	bool doTurn = false;
};

