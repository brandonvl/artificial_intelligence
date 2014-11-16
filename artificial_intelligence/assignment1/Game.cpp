#include "Game.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Drawer.h"
#include "GameObject.h"
#include "Cow.h"
#include "Rabbit.h"
#include <memory>

Game::Game()
{
	_graph = new Graph();
	_drawer = new Drawer("KMINT - Application 1",1024,720);
	_drawer->load("cow", R"(assets\cow.png)");
	_drawer->load("rabbit", R"(assets\rabbit.png)");

	_graph->addVertex("vert1", 100, 100);
	_graph->addVertex("vert2", 250, 60);
	_graph->addVertex("vert3", 100, 250);
	_graph->addVertex("vert4", 400, 400);
	_graph->addVertex("vert5", 700, 100);
	_graph->addVertex("vert6", 700, 570);

	_graph->addEdge("vert1", "vert2", 5);
	_graph->addEdge("vert1", "vert3", 10);
	_graph->addEdge("vert3", "vert4", 3);
	_graph->addEdge("vert2", "vert3", 15);
	_graph->addEdge("vert2", "vert5", 10);
	_graph->addEdge("vert2", "vert6", 5);
	_graph->addEdge("vert6", "vert5", 1);


	GameObject *rabbit = new Rabbit();

	_cow = new Cow();
	_graph->getVertex("vert1")->setData(*_cow);
	_graph->getVertex("vert3")->setData(*rabbit);

	_gameObjects.push_back(_cow);
	_gameObjects.push_back(rabbit);
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
	for (auto obj : _gameObjects) {
		obj->update(*this);
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
			_cow->moveRandom(*this);
		}
	}
}

void Game::draw()
{
	_drawer->prepareForDraw();
	_drawer->setDrawColor(0, 0, 0);
	std::map<std::string, Vertex*> vertexMap = _graph->getVertexes();
	for (auto it : vertexMap) {

		std::vector<Edge*> _edges = it.second->getEdges();

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