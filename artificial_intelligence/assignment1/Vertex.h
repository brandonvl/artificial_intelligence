#pragma once

#include <vector>
#include <string>

class Edge;
class GameObject;

class Vertex
{
public:
	Vertex(const std::string &key) : _key(key), _data(nullptr) {};
	virtual ~Vertex();
	void addEdge(const std::string &destination);
	void setData(GameObject &data) { _data = &data; }
	void clearData() { _data = nullptr; }
	GameObject *getData() { return _data; }
	const std::string &getKey() { return _key; }
	std::vector<Edge*> &getEdges() { return _edges; }
private:
	std::string _key;
	std::vector<Edge*> _edges;
	GameObject *_data;
};

