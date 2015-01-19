#include "SteeringBehaviors.h"
#include "2D\Transformations.h"
#include "Vehicle.h"
#include <iostream>


SteeringBehaviors::SteeringBehaviors(Vehicle *owner) : _owner(owner), _steeringForce(0,0)
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

Vector2D SteeringBehaviors::calculate() {

	_steeringForce.Zero();

	if (on(BEHAVIOR::PURSUIT))
		_steeringForce += pursuit(_target);
	if (on(BEHAVIOR::ARRIVE))
		_steeringForce += arrive(*_target->getPos(), Deceleration::normal);
	if (on(BEHAVIOR::WANDER))
		_steeringForce += wander();
	if (on(BEHAVIOR::EVADE))
		_steeringForce += evade(_target);

	_steeringForce.Truncate(_owner->getMaxSpeed());

	return _steeringForce;
}

SteeringBehaviors::~SteeringBehaviors()
{
}
