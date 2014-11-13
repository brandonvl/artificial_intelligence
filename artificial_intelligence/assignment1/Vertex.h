#pragma once

#include <vector>
#include <string>

class Edge;
class GameObject;

class Vertex
{
public:
	Vertex(const std::string &key, const float &xPos, const float &yPos) : _key(key), _xPos(xPos), _yPos(yPos), _data(nullptr) {};
	virtual ~Vertex();
	void addEdge(const std::string &destination, const int &weight);
	void setData(GameObject &data) { _data = &data; }
	void clearData() { _data = nullptr; }
	GameObject *getData() { return _data; }
	const std::string &getKey() { return _key; }
	std::vector<Edge*> &getEdges() { return _edges; }
	float getXPos() { return _xPos; }
	float getYPos() { return _yPos; }
private:
	float _xPos;
	float _yPos;
	std::string _key;
	std::vector<Edge*> _edges;
	GameObject *_data;
};

