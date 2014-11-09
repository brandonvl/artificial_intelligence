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

void Graph::addVertex(const std::string &vertKey)
{
	if (_vertexMap.find(vertKey) != _vertexMap.end()) {
		_vertexMap.insert(std::make_pair(vertKey, new Vertex()));
	}
}

void Graph::addEdge(const std::string &fromVert, const std::string &toVert)
{
	if (_vertexMap.find(fromVert) != _vertexMap.end() && _vertexMap.find(toVert) != _vertexMap.end()) {
		_vertexMap[fromVert]->addEdge(toVert);
	}
}
