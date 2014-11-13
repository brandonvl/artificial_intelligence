#pragma once

#include <string>

class GameObject
{
public:
	GameObject(const std::string &name) : _name(name) {};
	~GameObject();
	std::string getName() { return _name; }
private:
	std::string _name;
};

