#include "Vehicle.h"
#include "Telegram.h"
#include "Game.h"
#include "Drawer.h"
#include "2D\Transformations.h"

Vehicle::Vehicle(Vector2D *position,
	double    rotation,
	Vector2D *velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale) : MovingEntity(position,
	scale,
	velocity,
	max_speed,
	new Vector2D(sin(rotation), -cos(rotation)),
	mass,
	new Vector2D(scale, scale),
	max_turn_rate,
	max_force), _behaviors(this)

	//m_pWorld(world),
	//m_vSmoothedHeading(Vector2D(0, 0)),
	//m_bSmoothingOn(false),
	//m_dTimeElapsed(0.0)
{
	initBuffer();
	_drawColor = { 0, 0, 0 };
}


Vehicle::~Vehicle()
{
}

void Vehicle::draw(Game &game)
{
	std::vector<Vector2D> vectors;

	

	vectors = WorldTransform(_drawBuffer,
		*getConstPos(),
		*getHeading(),
		*getSide(),
		*getScale());

	game.getDrawer().setDrawColor(_drawColor.R, _drawColor.G, _drawColor.B);

	for (int i = 1; i < vectors.size(); ++i) {
		game.getDrawer().drawLine(vectors[i - 1].x, vectors[i - 1].y, vectors[i].x, vectors[i].y);
	}

	game.getDrawer().drawLine(vectors[2].x,vectors[2].y,vectors[0].x, vectors[0].y);
}

bool Vehicle::handleMessage(const Telegram &msg)
{
	return true;
}

void Vehicle::update(Game &game, const double &time_elapsed)
{
	//update the time elapsed
	_time_elapsed = time_elapsed;

	//keep a record of its old position so we can update its cell later
	//in this method
	Vector2D OldPos = *getPos();


	Vector2D SteeringForce{ 0.0, 0.0 };

	//calculate the combined force from each steering behavior in the 
	//vehicle's list
	SteeringForce = _behaviors.calculate();

	//Acceleration = Force/Mass
	Vector2D acceleration = SteeringForce / getMass();

	//update velocity
	*getVelocity() += acceleration * time_elapsed;

	//make sure vehicle does not exceed maximum velocity
	getVelocity()->Truncate(getMaxSpeed());

	//update the position
	*getPos() += *getVelocity() * time_elapsed;

	//update the heading if the vehicle has a non zero velocity
	if (getVelocity()->LengthSq() > 0.00000001)
	{
		*getHeading() = Vec2DNormalize(*getVelocity());

		*getSide() = getHeading()->Perp();
	}

	//EnforceNonPenetrationConstraint(this, World()->Agents());

	//treat the screen as a toroid
	WrapAround(*getPos(), game.getDrawer().getWindowWidth(), game.getDrawer().getWindowHeight());
}

void Vehicle::initBuffer()
{
	_drawBuffer =
	{ Vector2D(-1.0f, 1.0f),
	Vector2D(1.0f, 0.0f),
	Vector2D(-1.0f, -1.0f) };
}
