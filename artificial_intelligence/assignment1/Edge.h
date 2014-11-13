#pragma once

#include <string>

class Edge
{
public:
	Edge(const std::string &destination, const int &weight) : _destination(destination), _weight(weight) {};
	virtual ~Edge() {};
	std::string &getDestination() { return _destination; };
	int getWeight() { return _weight; }
	void setWeight(const int &weight) { _weight = weight; }
	void setDestination(std::string &destination) { _destination = destination; }
private:
	std::string _destination;
	int _weight;

};

