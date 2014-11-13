#include "SDL.h"
#include <iostream>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "GameObject.h"
#include <string>

void draw(Graph &graph);

int main(int argc, char **argv)
{

	SDL_Init(SDL_INIT_VIDEO);

	Graph graph;

	graph.addVertex("vert1", 100, 100);
	graph.addVertex("vert2", 250, 60);
	graph.addVertex("vert3", 100, 250);
	graph.addVertex("vert4", 400, 400);

	graph.addEdge("vert1", "vert2", 5);
	graph.addEdge("vert1", "vert3", 10);
	graph.addEdge("vert3", "vert4", 3);
	graph.addEdge("vert2", "vert4", 15);

	draw(graph);

	//std::cin.get();
	SDL_Quit();

	return 0;
}

void draw(Graph &graph)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	// Create the window where we will draw.
	window = SDL_CreateWindow("KMINT - Application 1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 720,
		0);
	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	renderer = SDL_CreateRenderer(window,
		-
		1, 0);

	// Select the color for drawing. It is set to red here.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);

	std::map<std::string, Vertex*> vertexMap = graph.getVertexes();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (auto it : vertexMap) {
		SDL_Rect *rect = new SDL_Rect();
		rect->h = 50;
		rect->w = 50;
		rect->x = it.second->getXPos();
		rect->y = it.second->getYPos();
		SDL_RenderFillRect(renderer, rect);

		if (it.second->getEdges().size() > 0)
		SDL_RenderDrawLine(renderer, it.second->getXPos(), it.second->getYPos(), graph.getVertex(it.second->getEdges()[0]->getDestination())->getXPos(), graph.getVertex(it.second->getEdges()[0]->getDestination())->getYPos());
	}

	// Up until now everything was drawn behind the scenes.
	// This will show the new, red contents of the window.
	SDL_RenderPresent(renderer);
	// Give us time to see the window.
	SDL_Delay(3000);
	// Always be sure to clean up
}

