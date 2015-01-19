#include "Drawer.h"
#include "Sprite.h"
#include "SDL_image.h"
#include "Game.h"

Drawer::Drawer(const std::string &title,const int &width, const int &height)
{
	_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		0);

	_width = width;
	_height = height;

	_renderer = SDL_CreateRenderer(_window,
		-
		1, 0);
}


Drawer::~Drawer()
{
	for (auto it : _sprites) {
		delete it.second;
	}
}

void Drawer::prepareForDraw() {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}

void Drawer::render() {
	SDL_RenderPresent(_renderer);
}


void Drawer::setDrawColor(const int &r, const int &b, const int &g)
{
	SDL_SetRenderDrawColor(_renderer, r, b, g, 255);
}

void Drawer::drawRectangle(const int &x, const int &y, const int &width, const int &height)
{	
	SDL_Rect *rect = new SDL_Rect();
	rect->h = height;
	rect->w = width;
	rect->x = x;
	rect->y = y;
	SDL_RenderFillRect(_renderer, rect);
}

void Drawer::drawLine(const int &x1, const int &y1, const int &x2, const int &y2)
{
	SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void Drawer::load(const std::string &key, const std::string &fileName)
{
	if (_sprites.find(key) == _sprites.end()) {
		if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
			SDL_Surface *surface = IMG_Load(fileName.c_str());

			if (surface != nullptr) {
				SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

				Sprite *sprite = new Sprite(texture, surface->w, surface->h);

				_sprites.insert(std::make_pair(key, sprite));

				SDL_FreeSurface(surface);
			}
		}
	}
}

void Drawer::drawSprite(const std::string &key, const int &x, const int &y)
{
	Sprite *sprite = _sprites[key];

	if (sprite != nullptr) {
		SDL_Rect *rect = new SDL_Rect();
		rect->x = x;
		rect->y = y;
		rect->w = DRAW_SIZE;
		rect->h = DRAW_SIZE;

		SDL_RenderCopy(_renderer, sprite->getSprite(), nullptr, rect);
	}
}

void Drawer::draw(const std::string &key, const int &x, const int &y)
{
	Sprite *sprite = _sprites[key];

	if (sprite != nullptr) {
		SDL_Rect rect = { x, y, sprite->getWidth(), sprite->getHeight() };
		SDL_RenderCopy(_renderer, sprite->getSprite(), nullptr, &rect);
	}
}

void Drawer::setColorOverLay(const std::string &key, Uint8 r, Uint8 g, Uint8 b)
{
	Sprite *sprite = _sprites[key];

	SDL_SetTextureColorMod(sprite->getSprite(), r, g, b);
}
