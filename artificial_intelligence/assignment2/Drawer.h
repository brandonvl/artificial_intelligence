#pragma once

#include "SDL.h"
#include <string>
#include <map>

class Sprite;

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
	void render();
private:
	std::map<std::string, Sprite*> _sprites;
	SDL_Renderer *_renderer;
	SDL_Window *_window;
};

