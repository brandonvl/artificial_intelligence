#pragma once

#include <vector>
#include <string>
#include <set>

class Edge;
class GameObject;

class Vertex
{
public:
	Vertex(const int &key, const float &xPos, const float &yPos) : _key(key), _xPos(xPos), _yPos(yPos) {};
	virtual ~Vertex();
	void setData(GameObject &data);
	void removeData(GameObject &data);
	void clearData() { _data.clear(); }
	std::set<GameObject*> getData() { return _data; }
	const int &getKey() { return _key; }
	float getXPos() { return _xPos; }
	float getYPos() { return _yPos; }
private:
	float _xPos;
	float _yPos;
	int _key;
	std::set<GameObject*> _data;
};

