#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

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
		_vertexMap[fromVert]->addEdge(toVert, weight);
	}
}

Vertex *Graph::getVertex(const std::string &vertKey) {
	return _vertexMap[vertKey];
}
