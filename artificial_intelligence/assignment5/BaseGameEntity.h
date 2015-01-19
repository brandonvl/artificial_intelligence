#pragma once

#include "2D\Vector2D.h"

class Game;
struct Telegram;
class GameGeneticInstance;

class BaseGameEntity
{
private:

	int _id;
	bool _tag;
	static int _nextValidId;

	void setID(int id = -1); // Legacy
	int nextValidID() { return _nextValidId++; }
protected:
	Vector2D *_scale;
	Vector2D *_pos;
	double _bradius;
	GameGeneticInstance *_gameGeneticInstance;
public:
	void setGameGeneticInstance(GameGeneticInstance &instance) { _gameGeneticInstance = &instance; }
	BaseGameEntity() :_id(nextValidID()),
		_bradius(0.0),
		_pos(new Vector2D()),
		_scale(new Vector2D(1.0, 1.0)),
		//m_EntityType(default_entity_type),
		_tag(false)
	{}

	BaseGameEntity(int entity_type) :_id(nextValidID()),
		_bradius(0.0),
		_pos(new Vector2D()),
		_scale(new Vector2D(1.0, 1.0)),
		//m_EntityType(entity_type),
		_tag(false)
	{}

	BaseGameEntity(int entity_type, Vector2D *pos, double r) : _pos(pos),
		_bradius(r),
		_id(nextValidID()),
		_scale(new Vector2D(1.0, 1.0)),
		//m_EntityType(entity_type),
		_tag(false)

	{}

	virtual ~BaseGameEntity() { delete _pos; delete _scale; }
	virtual bool handleMessage(const Telegram &msg) = 0;
	virtual void update(Game &game, const double &time_elapsed) = 0;
	virtual void draw(Game &game) = 0;
	int getId() const { return _id; }
	Vector2D *getScale() const { return _scale; }
	double getBradius() const { return _bradius; }
	void setScale(Vector2D &scale) { _scale = &scale; }
	void setBradius(const double &bradius) { _bradius = bradius; }
	void setPosition(Vector2D &pos) { _pos = &pos; }
	Vector2D *getConstPos() const { return _pos; }
	Vector2D *getPos() { return _pos; }
};
