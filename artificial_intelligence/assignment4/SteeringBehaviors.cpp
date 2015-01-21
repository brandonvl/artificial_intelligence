#include "SteeringBehaviors.h"
#include "2D\Transformations.h"
#include "Vehicle.h"
#include "Game.h"
#include "BaseGameEntity.h"
#include "Cow.h"
#include <iostream>


SteeringBehaviors::SteeringBehaviors(Vehicle *owner) : _owner(owner), _steeringForce(0, 0)
{
	_wanderRadius = 6.0;
	_wanderDistance = 3.0;
	_wanderJitter = 1000;

	double theta = RandFloat() * TwoPi;

	_wanderTarget = Vector2D(_wanderRadius * cos(theta),
		_wanderRadius * sin(theta));
}

Vector2D SteeringBehaviors::seek(Vector2D targetPos) {
	Vector2D desiredVelocity = Vec2DNormalize(targetPos - *_owner->getPos()) * _owner->getMaxSpeed();

	return (desiredVelocity - *_owner->getVelocity());
}

Vector2D SteeringBehaviors::flee(Vector2D targetPos) {

	if (Vec2DDistanceSq(*_owner->getPos(), targetPos) > _fleeDistance)
		return Vector2D(0, 0);

	Vector2D desiredVelocity = Vec2DNormalize(*_owner->getPos() - targetPos) * _owner->getMaxSpeed();

	return (desiredVelocity - *_owner->getVelocity());

}

Vector2D SteeringBehaviors::arrive(Vector2D targetPos, Deceleration deceleration) {
	Vector2D toTarget = targetPos - *_owner->getPos();

	double dist = toTarget.Length();

	if (dist > 0) {
		const double decelerationTweaker = 0.3;

		double speed = dist / ((double)deceleration * decelerationTweaker);

		speed = min(speed, _owner->getMaxSpeed());

		Vector2D desiredVelocity = toTarget * speed / dist;

		return (desiredVelocity - *_owner->getVelocity());
	}

	return Vector2D(0, 0);
}

Vector2D SteeringBehaviors::wander()
{

	double jitterThisTimeSlice = _wanderJitter * _owner->getTimeElapsed();
	//std::cout << jitterThisTimeSlice << "\n";
	_wanderTarget += Vector2D(RandomClamped() * jitterThisTimeSlice, RandomClamped() * jitterThisTimeSlice);

	_wanderTarget.Normalize();

	_wanderTarget *= _wanderRadius;

	Vector2D targetLocal = _wanderTarget + Vector2D(_wanderDistance, 0);

	Vector2D targetWorld = PointToWorldSpace(targetLocal, *_owner->getHeading(), *_owner->getSide(), *_owner->getPos());

	return (targetWorld - *_owner->getPos());
}

Vector2D SteeringBehaviors::separation(const std::vector<Vehicle*> &neighbors)
{
	Vector2D steeringForce;

	for (int i = 0; i < neighbors.size(); ++i)
	{
		if ((neighbors[i] != _owner) && neighbors[i]->isTagged())
		{
			Vector2D toAgent = *_owner->getPos() - *neighbors[i]->getPos();

			steeringForce += Vec2DNormalize(toAgent) / toAgent.Length();
		}
	}

	return steeringForce;
}

Vector2D SteeringBehaviors::alignment(const std::vector<Vehicle*> &neighbors)
{
	Vector2D averageHeading;

	int neighborCount = 0;

	for (int i = 0; i < neighbors.size(); ++i)
	{
		if ((neighbors[i] != _owner) && neighbors[i]->isTagged())
		{
			averageHeading += *neighbors[i]->getHeading();

			++neighborCount;
		}
	}

	if (neighborCount > 0)
	{
		averageHeading /= (double)neighborCount;

		averageHeading -= *_owner->getHeading();
	}

	return averageHeading;
}

Vector2D SteeringBehaviors::cohesion(const std::vector<Vehicle*> &neighbors)
{
	Vector2D centerOfMass, steeringForce;

	int neighborCount = 0;

	for (int i = 0; i < neighbors.size(); ++i)
	{
		if ((neighbors[i] != _owner) && neighbors[i]->isTagged())
		{
			centerOfMass += *neighbors[i]->getPos();

			++neighborCount;
		}
	}

	if (neighborCount > 0)
	{
		centerOfMass /= (double)neighborCount;

		steeringForce = seek(centerOfMass);
	}

	return steeringForce;
}

void SteeringBehaviors::pursuitOn(Vehicle *evader) {
	_target = evader;
	_behavior |= BEHAVIOR::PURSUIT;
}

void SteeringBehaviors::pursuitOff()
{
	if (on(BEHAVIOR::PURSUIT))
		_behavior ^= BEHAVIOR::PURSUIT;
}

void SteeringBehaviors::arriveOn(Vehicle *evader)
{
	_target = evader;
	_behavior |= BEHAVIOR::ARRIVE;
}

void SteeringBehaviors::arriveOff()
{
	if (on(BEHAVIOR::ARRIVE))
		_behavior ^= BEHAVIOR::ARRIVE;
}

void SteeringBehaviors::evadeOn(Vehicle *pursuer, double fleeDistance)
{
	_fleeDistance = fleeDistance;
	_target = pursuer;
	_behavior |= BEHAVIOR::EVADE;
}

void SteeringBehaviors::evadeOff()
{
	if (on(BEHAVIOR::EVADE))
		_behavior ^= BEHAVIOR::EVADE;
}

void SteeringBehaviors::wanderOn()
{
	_behavior |= BEHAVIOR::WANDER;
}

void SteeringBehaviors::wanderOff()
{
	if (on(BEHAVIOR::WANDER))
		_behavior ^= BEHAVIOR::WANDER;
}

void SteeringBehaviors::separationOn()
{
	_behavior |= BEHAVIOR::SEPARATION;
}

void SteeringBehaviors::separationOff()
{
	if (on(BEHAVIOR::SEPARATION))
		_behavior ^= BEHAVIOR::SEPARATION;
}

void SteeringBehaviors::alignmentOn()
{
	_behavior |= BEHAVIOR::ALIGNMENT;
}

void SteeringBehaviors::alignmentOff()
{
	if (on(BEHAVIOR::ALIGNMENT))
		_behavior ^= BEHAVIOR::ALIGNMENT;
}

void SteeringBehaviors::cohesionOn()
{
	_behavior |= BEHAVIOR::COHESION;
}

void SteeringBehaviors::cohesionOff()
{
	if (on(BEHAVIOR::COHESION))
		_behavior ^= BEHAVIOR::COHESION;
}

Vector2D SteeringBehaviors::pursuit(const Vehicle *evader) {

	Vector2D toEvader = *evader->getConstPos() - *_owner->getPos();

	double relativeHeading = _owner->getHeading()->Dot(*evader->getHeading());

	if ((toEvader.Dot(*_owner->getHeading()) > 0) && (relativeHeading < -0.95))
		return seek(*evader->getConstPos());

	double lookAheadTime = toEvader.Length() / (_owner->getMaxSpeed() + evader->getVelocity()->Length());

	return seek(*evader->getConstPos() + *evader->getVelocity() * lookAheadTime);
}

Vector2D SteeringBehaviors::evade(const Vehicle *pursuer) {

	Vector2D toPursuer = *pursuer->getConstPos() - *_owner->getPos();

	double lookAheadTime = toPursuer.Length() / (_owner->getMaxSpeed() + pursuer->getVelocity()->Length());

	return flee(*pursuer->getConstPos() + *pursuer->getVelocity() * lookAheadTime);
}

void SteeringBehaviors::TagNeighbors(double radius)
{
	auto neighbors = _owner->getWorld().getCows();
	for (auto neighbor : neighbors)
	{
		neighbor->setIsTagged(false);

		Vector2D to = *neighbor->getPos() - *_owner->getPos();

		double range = radius + neighbor->getBradius();

		if ((neighbor != _owner) && (to.LengthSq() < range*range))
		{
			neighbor->setIsTagged(true);
		}
	}
}

bool SteeringBehaviors::AccumulateForce(Vector2D &runningTot, Vector2D forceToAdd)
{
	double magnitudeSoFar = runningTot.Length();

	double magnitudeRemaining = _owner->getMaxForce() - magnitudeSoFar;

	if (magnitudeRemaining <= 0.0) return false;

	double magnitudeToAdd = forceToAdd.Length();

	if (magnitudeToAdd < magnitudeRemaining)
	{
		runningTot += forceToAdd;
	}
	else
	{
		runningTot += (Vec2DNormalize(forceToAdd) * magnitudeRemaining);
	}

	return true;
}

Vector2D SteeringBehaviors::calculate() {
	
	_steeringForce.Zero();

	if (_type == CalculateType::Weighted)
		calculateWeight();
	else if (_type == CalculateType::Priority)
		calculatePriority();

	_steeringForce.Truncate(_owner->getMaxSpeed());

	return _steeringForce;
}

void SteeringBehaviors::calculateWeight()
{
	if (on(BEHAVIOR::SEPARATION))
		_steeringForce += separation(_owner->getWorld().getCows());
	if (on(BEHAVIOR::ALIGNMENT))
		_steeringForce += alignment(_owner->getWorld().getCows());
	if (on(BEHAVIOR::COHESION))
		_steeringForce += cohesion(_owner->getWorld().getCows());
	if (on(BEHAVIOR::PURSUIT))
		_steeringForce += pursuit(_target);
	if (on(BEHAVIOR::ARRIVE))
		_steeringForce += arrive(*_target->getPos(), Deceleration::normal);
	if (on(BEHAVIOR::WANDER))
		_steeringForce += wander();
	if (on(BEHAVIOR::EVADE))
		_steeringForce += evade(_target);
}

void SteeringBehaviors::calculatePriority()
{
	//  double weightPursuit = 10.0, weightSeperation = 5, weightCohesion = 15, weightAlignment = 20, weightWander = 1;
	double weightPursuit = 1.0, weightSeperation = 20, weightCohesion = 0.8, weightAlignment = 20, weightWander = 1;

	if (on(BEHAVIOR::SEPARATION) || on(BEHAVIOR::ALIGNMENT) || on(BEHAVIOR::COHESION))
		TagNeighbors(100.0);

	if (on(BEHAVIOR::SEPARATION))
	{
		Vector2D force = separation(_owner->getWorld().getCows()) * weightSeperation;

		if (!AccumulateForce(_steeringForce, force)) return;
	}
	if (on(BEHAVIOR::ALIGNMENT))
	{
		Vector2D force = alignment(_owner->getWorld().getCows()) * weightAlignment;

		if (!AccumulateForce(_steeringForce, force)) return;
	}
	if (on(BEHAVIOR::COHESION))
	{
		Vector2D force = cohesion(_owner->getWorld().getCows()) * weightCohesion;

		if (!AccumulateForce(_steeringForce, force)) return;
	}
	if (on(BEHAVIOR::PURSUIT))
	{
		Vector2D force = pursuit(_target) * weightSeperation;

		if (!AccumulateForce(_steeringForce, force)) return;
	}
	if (on(BEHAVIOR::WANDER))
	{
		Vector2D force = _steeringForce += wander() *weightWander;

		if (!AccumulateForce(_steeringForce, force)) return;
	}
}

SteeringBehaviors::~SteeringBehaviors()
{
}