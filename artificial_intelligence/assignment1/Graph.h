#pragma once

#include <string>
#include <map>

class Vertex;
class Edge;

class Graph
{
public:
	Graph();
	virtual ~Graph();
	void addEdge(const std::string &fromVert, const std::string &toVert, const int &weight);
	void addVertex(const std::string &vertKey, const float &xPos, const float &yPos);
	Vertex *getVertex(const std::string &vertKey);
	std::map<std::string, Vertex*> getVertexes() { return _vertexMap; }
private:
	std::map<std::string, Vertex*> _vertexMap;
};

