#pragma once
#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class Vehicle :
	public MovingEntity
{
private:
	std::vector<Vector2D> _drawBuffer;
	void initBuffer();
protected:
	double _time_elapsed;
	SteeringBehaviors _behaviors;
	struct DrawColor {
		int R; int G; int B;
	};

	DrawColor _drawColor;

public:
	Vehicle(Vector2D *position,
		double    rotation,
		Vector2D *velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);
	virtual ~Vehicle();
	SteeringBehaviors &getSteeringBehaviors() { return _behaviors; }
	virtual double getTimeElapsed() { return _time_elapsed; }
	virtual bool handleMessage(const Telegram &msg) override;
	virtual void update(Game &game, const double &time_elapsed) override;
	virtual void draw(Game &game) override;
	virtual void setDrawColor(const int &r, const int &g, const int &b) {
		_drawColor = { r, g, b };
	}
};

