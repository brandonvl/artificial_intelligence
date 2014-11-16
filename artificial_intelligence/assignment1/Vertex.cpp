#include "Vertex.h"
#include "Edge.h"
#include "GameObject.h"

Vertex::~Vertex()
{
}


void Vertex::addEdge(const std::string &destination, const int &weight)
{
	_edges.push_back(new Edge(destination, weight));
}

void Vertex::setData(GameObject &data)
{
	Vertex *prevField = data.getField();

	if (prevField != nullptr)
		prevField->clearData();

	_data = &data;
	data.setField(this);
}