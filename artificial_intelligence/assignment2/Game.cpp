#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Drawer.h"
#include "GameObject.h"
#include "Cow.h"
#include "Rabbit.h"
#include <memory>
#include <list>

Game::Game()
{
	_graph = new Graph();
	_drawer = new Drawer("KMINT - Application 1",1024,720);
	_drawer->load("cow", R"(assets\cow.png)");
	_drawer->load("rabbit", R"(assets\rabbit.png)");

	_graph->addVertex(1, 100, 100);
	_graph->addVertex(2, 250, 60);
	_graph->addVertex(3, 100, 250);
	_graph->addVertex(4, 400, 400);
	_graph->addVertex(5, 700, 100);
	_graph->addVertex(6, 700, 570);
	_graph->addVertex(7, 800, 350);
	_graph->addVertex(8, 900, 600);

	_graph->addEdge(1, 2, 50000);
	_graph->addEdge(1, 3, 100000);
	_graph->addEdge(3, 4, 30000);
	_graph->addEdge(2, 3, 150000);
	_graph->addEdge(2, 5, 100000);
	_graph->addEdge(2, 6, 50000);
	_graph->addEdge(6, 5, 100000);
	_graph->addEdge(5, 7, 10000);
	_graph->addEdge(7, 8, 30000);


	_cow = new Cow();
	_rabbit = new Rabbit();
	_graph->getVertex(1)->setData(*_cow);
	_graph->getVertex(6)->setData(*_rabbit);

	_gameObjects.push_back(_rabbit);
	_gameObjects.push_back(_cow);
	
}


Game::~Game()
{
	delete _graph;
	delete _drawer;
}

void Game::stop() {
	_running = false;
}

void Game::run()
{
	_running = true;

	while (_running) {
		handleEvents();
		update();
		draw();
		//SDL_Delay(1000);
	}
}

void Game::update()
{
	if (doTurn) {
		for (auto obj : _gameObjects) {
			obj->update(*this);
		}
		doTurn = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
			stop();
		}
		else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
			// do algorithm
			doTurn = true;
		}
	}
}

void Game::draw()
{
	_drawer->prepareForDraw();
	_drawer->setDrawColor(0, 0, 0);
	std::map<int, Vertex*> vertexMap = _graph->getVertexes();
	for (auto it : vertexMap) {

		std::list<Edge*> _edges = _graph->getEdges(it.second->getKey());

		for (auto edge : _edges) {
			Vertex *destination = _graph->getVertex(edge->getDestination());

			if (destination != nullptr)
				_drawer->drawLine(it.second->getXPos() + VERTEX_MIDDLE, it.second->getYPos() + VERTEX_MIDDLE, destination->getXPos() + VERTEX_MIDDLE, destination->getYPos() + VERTEX_MIDDLE);
		}

		_drawer->drawRectangle(it.second->getXPos(), it.second->getYPos(), VERTEX_SIZE, VERTEX_SIZE);

		GameObject *object = it.second->getData();

		if (object != nullptr) {
			_drawer->drawSprite(object->getName(), it.second->getXPos(), it.second->getYPos());
		}
	}

	_drawer->render();
}