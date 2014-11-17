#pragma once

#include <map>
#include <list>

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
	Edge *getEdge(const int &from, const int &to);
	std::list<Edge*> getEdges(const int &key) { return _edgeList[key]; }
	std::map<int, Vertex*> getVertexes() { return _vertexMap; }
	Vertex *getRandomVertex(const int &notKey);
private:
	std::map<int, Vertex*> _vertexMap;
	std::map<int, std::list<Edge*>> _edgeList;
};

