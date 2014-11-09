#pragma once

#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();
	const std::string getName();
private:
	std::string _name;
	float _xPosition;
	float _yPosition;
};

