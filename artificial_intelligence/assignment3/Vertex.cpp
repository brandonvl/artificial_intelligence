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
		prevField->removeData(data);

	_data.insert(&data);
	data.setField(this);
}

void Vertex::removeData(GameObject &data)
{
	_data.erase(&data);
}