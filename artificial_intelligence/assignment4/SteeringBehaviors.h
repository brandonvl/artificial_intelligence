#pragma once

#include "2D\Vector2D.h"
#include <vector>

class Vehicle;

enum class Deceleration { slow = 3, normal = 2, fast = 1 };

class SteeringBehaviors
{
public:

	enum CalculateType
	{
		Weighted,
		Priority
	};

	void pursuitOn(Vehicle *evader);
	void pursuitOff();
	bool isPursuitOn() { return on(BEHAVIOR::PURSUIT); }

	void arriveOn(Vehicle *evader);
	void arriveOff();
	bool isArriveOn() { return on(BEHAVIOR::ARRIVE); }

	void evadeOn(Vehicle *pursuer, double fleeDistance);
	void evadeOff();
	bool isEvadeOn() { return on(BEHAVIOR::EVADE); }

	void wanderOn();
	void wanderOff();
	bool isWanderOn() { return on(BEHAVIOR::WANDER); }

	void separationOn();
	void separationOff();
	bool isSeparationOn() { return on(BEHAVIOR::SEPARATION); }

	void alignmentOn();
	void alignmentOff();
	bool isAlignmentOn() { return on(BEHAVIOR::ALIGNMENT); }

	void cohesionOn();
	void cohesionOff();
	bool isCohesionOn() { return on(BEHAVIOR::COHESION); }

	SteeringBehaviors(Vehicle *owner);
	virtual ~SteeringBehaviors();
	Vector2D calculate();
	Vector2D calculateWeight();
	Vector2D calculatePriority();

	void setCalculateType(CalculateType type) { _type = type; }

	void TagNeighbors(double radius);
	bool AccumulateForce(Vector2D &runningTot, Vector2D ForceToAdd);
private:
	enum BEHAVIOR
	{
		NONE = 0x00000,
		SEEK = 0x00002,
		FLEE = 0x00004,
		ARRIVE = 0x00008,
		WANDER = 0x00010,
		COHESION = 0x00020,
		SEPARATION = 0x00040,
		ALIGNMENT = 0x00080,
		PURSUIT = 0x00800,
		EVADE = 0x01000,
		FLOCK = 0x08000,
	};

	double _fleeDistance = 0;
	int _behavior;
	CalculateType _type;

	Vehicle *_owner;
	Vector2D _steeringForce;
	Vector2D seek(Vector2D targetPos);
	Vector2D flee(Vector2D targetPos);
	Vector2D evade(const Vehicle *pursuer);
	Vector2D pursuit(const Vehicle *evader);
	Vector2D arrive(Vector2D targetPos, Deceleration deceleration);
	Vector2D wander();
	Vector2D separation(const std::vector<Vehicle*> &neighbors);
	Vector2D alignment(const std::vector<Vehicle*> &neighbors);
	Vector2D cohesion(const std::vector<Vehicle*> &neighbors);

	Vehicle *_target;

	double _wanderRadius, _wanderDistance, _wanderJitter;
	Vector2D _wanderTarget;
	bool on(BEHAVIOR bt){ return (_behavior & bt) == bt; }
};