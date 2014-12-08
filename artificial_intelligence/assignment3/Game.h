#pragma once

#include <vector>

class Graph;
class Drawer;
class GameObject;
class Cow;
class Rabbit;

const int VERTEX_SIZE = 50;
const int VERTEX_MIDDLE = VERTEX_SIZE / 2;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
	void stop();
	Graph &getGraph() { return *_graph; }
	Rabbit &getRabbit() { return *_rabbit; }
	Drawer &getDrawer()  { return *_drawer; }
private:
	Graph *_graph;
	Drawer *_drawer;
	Cow *_cow;
	Rabbit *_rabbit;
	void handleEvents();
	void update();
	void draw();
	bool _running = false;
	bool doTurn = false;
};

