#include "Vertex.h"
#include "Edge.h"

Vertex::~Vertex()
{
}


void Vertex::addEdge(const std::string &destination, const int &weight)
{
	_edges.push_back(new Edge(destination, weight));
}