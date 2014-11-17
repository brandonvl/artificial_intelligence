#pragma once

#include <string>

class Edge
{
public:
	Edge(const int &from ,const int &to, const int &weight) : _from(from), _to(to), _weight(weight) {};
	virtual ~Edge() {};
	int &getSource() { return _from; }
	int &getDestination() { return _to; };
	int getWeight() { return _weight; }
	void setWeight(const int &weight) { _weight = weight; }
	void setDestination(int &to) { _to = to; }
	void setFrom(int &from) { _from = from; }
private:
	int _from;
	int _to;
	int _weight;

};

