#include <cmath>
#include "../../Include/Maths/Vector3.h"

using namespace Maths;


//	Constructor
//	-----------

Vector3f::Vector3f()
{
	x = y = z = 0.f;
}

Vector3f::Vector3f(float in_value)
{
	x = y = z = in_value;
}

Vector3f::Vector3f(float in_x, float in_y, float in_z)
{
	x = in_x;
	y = in_y;
	z = in_z;
};

Vector3f::Vector3f(const Vector3f& in_U, const Vector3f& in_V)
{
	x = in_V.x - in_U.x;
	y = in_V.y - in_U.y;
	z = in_V.z - in_U.z;
}



//	Internal Operators
//	------------------

void Maths::Vector3f::operator-=(const Vector3f& a)
{
	*this = *this - a;
}

void Maths::Vector3f::operator+=(const Vector3f& a)
{
	*this = *this + a;
}


void Maths::Vector3f::operator-=(const float a)
{
	*this = *this - a;
}

void Maths::Vector3f::operator+=(const float a)
{
	*this = *this + a;
}

void Maths::Vector3f::operator/=(const float a)
{
	*this = *this / a;
}

void Maths::Vector3f::operator*=(const float a)
{
	*this = *this * a;
}

//	Internal Function
//	-----------------

float Vector3f::squareLength() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector3f::length() const
{
	return sqrt(this->squareLength());
}

Vector3f  Vector3f::normalized() const
{
	float length = this->length();

	//	Avoid division by 0
	if (length != 0)
	{
		return { this->x / length, this->y / length, this->z / length };
	}
	return { 0.f,0.f,0.f };
}

Vector3f Vector3f::opposite() const
{
	return (*this) * (-1);
}

float Maths::dotProduct(const Vector3f& a, const Vector3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}


float Maths::getDistance(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a, b).length();
}



