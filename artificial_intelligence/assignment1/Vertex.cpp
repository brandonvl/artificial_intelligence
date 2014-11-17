#include "Vertex.h"
#include "Edge.h"
#include "GameObject.h"

Vertex::~Vertex()
{
}

void Vertex::setData(GameObject &data)
{
	Vertex *prevField = data.getField();

	if (prevField != nullptr)
		prevField->clearData();

	_data = &data;
	data.setField(this);
}