#pragma once

#include "SDL.h"
#include <string>
#include <map>

class Sprite;

const int DRAW_SIZE = 50;

class Drawer
{
public:
	Drawer(const std::string &title, const int &width, const int &height);
	virtual ~Drawer();
	void load(const std::string &key, const std::string &fileName);
	void prepareForDraw();
	void setDrawColor(const int &r, const int &b, const int &g);
	void setColorOverLay(const std::string &key, Uint8 r, Uint8 g, Uint8 b);
	void drawRectangle(const int &x, const int &y, const int &width, const int &height);
	void drawLine(const int &x1, const int &y1, const int &x2, const int &y2);
	void drawSprite(const std::string &key, const int &x, const int &y);
	void draw(const std::string &key, const int &x, const int &y);
	int getWindowWidth() { return _width; }
	int getWindowHeight() { return _height; }
	void render();
private:
	int _width;
	int _height;
	std::map<std::string, Sprite*> _sprites;
	SDL_Renderer *_renderer;
	SDL_Window *_window;
};

