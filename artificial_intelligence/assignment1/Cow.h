#pragma once
#include "GameObject.h"
#include <vector>

class Vertex;

class Cow :
	public GameObject
{
public:
	Cow() : GameObject("cow") { };
	virtual ~Cow();
	void update(Game &game) override;
	void moveRandom(Game &game) override;
private:
	std::vector<Vertex*> _path;
	bool _rabbitFound = false;
	bool _pathPrinted = false;
};

