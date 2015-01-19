#pragma once

#include <math.h>

class Vector2D
{
private:
	double x, y;
public:
	Vector2D() :x(0.0), y(0.0){}
	Vector2D(double a, double b) :x(a), y(b){}
	virtual ~Vector2D();
	void zero(){ x = 0.0; y = 0.0; }
	bool isZero()const{ return (x*x + y*y) <= 0.0; }
	double getX() const { return x; }
	double getY() const { return y; }
	double length()const;
	double lengthSq()const;
	void normalize();
	double dot(const Vector2D& v2)const;
	Vector2D *perp() const;

	const Vector2D& operator+=(const Vector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	const Vector2D& operator-=(const Vector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	const Vector2D& operator*=(const double& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	const Vector2D& operator/=(const double& rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	bool operator==(const Vector2D& rhs)const
	{
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(const Vector2D& rhs)const
	{
		return (x != rhs.x) || (y != rhs.y);
	}
};

