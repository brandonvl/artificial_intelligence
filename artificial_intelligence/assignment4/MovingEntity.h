#pragma once
#include "BaseGameEntity.h"
class MovingEntity :
	public BaseGameEntity
{
private:
	Vector2D *_velocity;
	Vector2D *_heading;
	Vector2D *_side;
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
public:
	Vector2D *getVelocity() const { return _velocity; }
	Vector2D *getHeading() const { return _heading; }
	Vector2D *getSide() const { return _side; }
	double getMass() { return _mass; }
	void setMass(const double &mass) { _mass = mass; }
	double getMaxSpeed() { return _maxSpeed; }
	void setMaxSpeed(const double &maxSpeed) { _maxSpeed = maxSpeed; }
	double getMaxForce() { return _maxForce; }
	void setForce(const double &maxForce) { _maxForce = maxForce; }
	double getMaxTurnRate() { return _maxTurnRate; }
	void setMaxTurnRate(const double &maxTurnRate) { _maxTurnRate = maxTurnRate; }
	MovingEntity(Vector2D *position,
		double    radius,
		Vector2D *velocity,
		double    max_speed,
		Vector2D *heading,
		double    mass,
		Vector2D *scale,
		double    turn_rate,
		double    max_force) :BaseGameEntity(0, position, radius),
		_heading(heading),
		_velocity(velocity),
		_mass(mass),
		_side(new Vector2D(_heading->Perp())),
		_maxSpeed(max_speed),
		_maxTurnRate(turn_rate),
		_maxForce(max_force)
	{
		_scale = scale;
	}
	virtual ~MovingEntity();
};

