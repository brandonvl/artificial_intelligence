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
	void addEdge(const std::string &fromVert, const std::string &toVert);
	void addVertex(const std::string &vertKey);
	Vertex &getVertex(const std::string &vertKey);
private:
	std::map<std::string, Vertex*> _vertexMap;
};

