#pragma once

#include <map>

class Vertex;
class Edge;

class Graph
{
public:
	Graph();
	virtual ~Graph();
	void addEdge(const int &fromVert, const int &toVert, const int &weight);
	void addVertex(const int &vertKey, const float &xPos, const float &yPos);
	Vertex *getVertex(const int &vertKey);
	std::map<int, Vertex*> getVertexes() { return _vertexMap; }
	Vertex *getRandomVertex(const int &notKey);
private:
	std::map<int, Vertex*> _vertexMap;
};

