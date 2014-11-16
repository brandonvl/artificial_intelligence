#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"

Graph::Graph()
{
}


Graph::~Graph()
{
	for (auto it : _vertexMap)
		delete it.second;
}

void Graph::addVertex(const std::string &vertKey, const float &xPos, const float &yPos)
{
	if (_vertexMap.find(vertKey) == _vertexMap.end()) {
		_vertexMap.insert(std::make_pair(vertKey, new Vertex(vertKey,xPos,yPos)));
	}
}

void Graph::addEdge(const std::string &fromVert, const std::string &toVert, const int &weight)
{
	if (_vertexMap.find(fromVert) != _vertexMap.end() && _vertexMap.find(toVert) != _vertexMap.end()) {
		_vertexMap[toVert]->addEdge(fromVert, weight);
		_vertexMap[fromVert]->addEdge(toVert, weight);
	}
}

Vertex *Graph::getRandomVertex(const std::string &notKey)
{
	Vertex *returnVertex = nullptr;
	int retries = 0;
	std::map<std::string, Vertex*>::const_iterator iterator;

	do
	{
		iterator = _vertexMap.begin();
		std::advance(iterator, RandomGenerator::random(0, _vertexMap.size()-1));
		if (iterator != _vertexMap.end()) {
			returnVertex = iterator->second;
		}

	} while (returnVertex == nullptr && retries < 10 && returnVertex->getKey() == notKey);

	return returnVertex;
}

Vertex *Graph::getVertex(const std::string &vertKey) 
{
	return _vertexMap[vertKey];
}
