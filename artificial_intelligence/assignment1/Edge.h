#pragma once

#include <string>

class Edge
{
public:
	Edge(const std::string &destination);
	virtual ~Edge();
	std::string &getDestination();
private:
	std::string _destination;
};

