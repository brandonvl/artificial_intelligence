#pragma once

#include "SDL.h"

class Sprite
{
public:
	Sprite(SDL_Texture *sprite, const int &width, const int &height) : _sprite(sprite), _width(width), _height(height) {};
	virtual ~Sprite() {
		SDL_DestroyTexture(_sprite);
	}
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	SDL_Texture *getSprite() { return _sprite; }
private:
	int _width;
	int _height;
	SDL_Texture *_sprite;
};

