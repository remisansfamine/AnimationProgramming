#pragma once
#include "Utils.h"


#define X_AXIS_VEC3 Vector3f(1.f,0.f,0.f)
#define Y_AXIS_VEC3 Vector3f(0.f,1.f,0.f)
#define Z_AXIS_VEC3 Vector3f(0.f,0.f,1.f)

namespace Maths
{
	union Vector3f
	{
		//	Variables
		//	---------
		float	c[3];
		struct { float x; float y; float z; };

		//	Constructors
		//	------------

		Vector3f();
		Vector3f(float in_value);
		Vector3f(float in_x, float in_y, float in_z);
		Vector3f(const Vector3f& in_U, const Vector3f& in_V);

		~Vector3f() {};

		//	Functions
		//	---------

		//	Return length of the current Vector3f
		//	Parameters : none
		//	-----------------
		float length() const;

		//	Return square length of the current Vector3f, if possible use it instead of length
		//	Parameters : none
		float squareLength() const;

		//	Return normalized Vector3f of the current one
		//	Parameters : none
		//	-----------------
		Vector3f normalized() const;

		//	Return the opposite direction of the current vector
		//	Parameters : none
		//	-----------------
		Vector3f opposite() const;

		//	Static Functions
		//	----------------

		//	Return a Vector3f with x, y and z equal to 0.0
		//	Parameters : none
		//	-----------------
		static Vector3f zero()	{ return { 0.f,0.f,0.f }; }

		//	Return a Vector3f with x, y and z equal to 1.0
		//	Parameters : none
		//	-----------------
		static Vector3f one()	{ return { 1.f,1.f,1.f }; }


		//	Return a Vector3f with only one on x axis
		//	Parameters : none
		//	-----------------
		static Vector3f xAxis() { return { 1.f,0.f,0.f }; }

		//	Return a Vector3f with only one on y axis
		//	Parameters : none
		//	-----------------
		static Vector3f yAxis() { return { 0.f,1.f,0.f }; }

		//	Return a Vector3f with only one on z axis
		//	Parameters : none
		//	-----------------
		static Vector3f zAxis() { return { 0.f,0.f,1.f }; }


		//	Operators
		//	---------

		//	Vector3f -= Vector3f
		//	--------------------
		void operator-=(const Vector3f& a);

		//	Vector3f += Vector3f
		//	--------------------
		void operator+=(const Vector3f& a);


		//	Vector3f -= float
		//	-----------------
		void operator-=(const float a);

		//	Vector3f += float
		//	-----------------
		void operator+=(const float a);

		//	Vector3f /= float
		//	-----------------
		void operator/=(const float a);

		//	Vector3f *= float
		//	-----------------
		void operator*=(const float a);
	};

	//	Return the dot prosuct between two Vector3f
	//	Parameters : const Vector3f& a, const Vector3f& b
	//	-------------------------------------------------
	float dotProduct(const Vector3f& a, const Vector3f& b);

	//	Return the distance between two Vector3f
	//	Parameters : const Vector3f& a, const Vector3f& b
	//	-------------------------------------------------
	float getDistance(const Vector3f& a, const Vector3f& b);

	//	Return the cross product between two Vector3f
	//	Parameters : const Vector3f& a, const Vector3f& b
	//	------------------------------------------------
	Vector3f vector3CrossProduct(const Vector3f& a, const Vector3f& b);

	//	Return the reflection of a vector depending on a normal
	//	Parameters : const Vector3f& in, const Vector3f& normal
	//	----------------------------------------
	Vector3f vector3Reflect(const Vector3f& in, const Vector3f& normal);

	//	Return the vector resulting of the linear interpolation of two other vectors
	//	Parameters : const Vector3f& in, const Vector3f& normal
	//	----------------------------------------
	Vector3f lerp(const Vector3f& in_a, const Vector3f& in_b, const float ratio);

	//	Return any orthogonal Vector of a Vector
	//	Parameters: const Vector3f& v
	//	----------------------
	Vector3f vector3Orthogonal(const Vector3f& v);

	
	//	Return a Vector3f with the following format ( x, 0.0, 0.0)
	//	Parameters : const float x
	//	-------------------------
	Vector3f xVector3(const float x);

	//	Return a Vector3f with the following format ( 0.0, y , 0.0)
	//	Parameters : const float y
	//	-------------------------
	Vector3f yVector3(const float y);

	//	Return a Vector3f with the following format ( 0.0, 0.0, z)
	//	Parameters : const float z
	//	-------------------------
	Vector3f zVector3(const float z);

	//	Return the perpendicular of a Vector3f from an axis
	//	Parameters : const Vector3f& v, const Vector3f& axis
	//	----------------------------------------------------
	Vector3f getVector3Perpendicular(const Vector3f& v, const Vector3f& axis);

	//	Return the projection of a Vector3f
	//	Parameters : const float dot, const Vector3f& axis
	//	--------------------------------------------------
	Vector3f getVector3Projection(const float dot, const Vector3f& axis);

	//	Return the projection of a Vector3f
	//	Parameters : const Vector3f& v, const Vector3f& axis
	//	----------------------------------------------------
	Vector3f getVector3Projection(const Vector3f& v, const Vector3f& axis);

	//	Vector3f - Vector3f
	//	-------------------
	Vector3f operator-(const Vector3f& a, const Vector3f& b);

	//	Vector3f + Vector3f
	//	-------------------
	Vector3f operator+(const Vector3f& a, const Vector3f& b);

	//	- Vector3f
	//	----------
	Vector3f operator-(const Vector3f& a);



	//	Vector3f == Vector3f
	//	--------------------
	bool operator==(const Vector3f& a, const Vector3f& b);

	//	Vector3f != Vector3f
	//	--------------------
	bool operator!=(const Vector3f& a, const Vector3f& b);

	//	Vector3f + Float
	//	----------------
	Vector3f    operator+(const Vector3f& a, const float value);

	//	Float + Vector3f
	//	----------------
	Vector3f    operator+(const float value, const Vector3f& a);

	//	Vector3f - Float
	//	----------------
	Vector3f    operator-(const Vector3f& a, const float value);

	//	Vector3f * Float
	//	----------------
	Vector3f    operator*(const Vector3f& a, const float scale);

	//	Float + Vector3f
	//	----------------
	Vector3f    operator*(const float value, const Vector3f& a);

	//	Vector3f / Float
	//	----------------
	Vector3f    operator/(const Vector3f& a, const float value);

}
#include "../../Inline/Maths/Vector3.inl"