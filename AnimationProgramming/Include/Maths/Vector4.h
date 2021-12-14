#pragma once

#include "Vector3.h"


/*========================    Vector 4    ========================*/

namespace Maths
{
	union Vector4f
	{

		//	Variables
		//	---------
		float e[4];
		struct { float x; float y; float z; float w; };
		struct { float r; float g; float b; float a; };
		Vector3f xyz;

		//	Constructors
		//	------------
		Vector4f();
		Vector4f(float in_value);
		Vector4f(float in_x, float in_y, float in_z);
		Vector4f(float in_x, float in_y, float in_z, float in_w);
		Vector4f(const Vector4f& in_U, const Vector4f& in_V);
		Vector4f(const Vector3f& in_xyz, const float in_w);

		~Vector4f() {};
	};

	//	Vector4f + Vector4f
	//	-------------------
	Vector4f	operator+(const Vector4f& a, const Vector4f& b);

	//	Vector4f - Vector4f
	//	-------------------
	Vector4f	operator-(const Vector4f& a, const Vector4f& b);

	//	Vector4f x Vector4f
	//	-------------------
	Vector4f	operator*(const Vector4f& a, const Vector4f& b);

	//	Vector4f / Vector4f
	//	-------------------
	Vector4f	operator/(const Vector4f& a, const Vector4f& b);

	//	- Vector4f
	//	----------
	Vector4f	operator-(const Vector4f& a);



	//	Vector4f + float
	//	----------------
	Vector4f	operator+(const Vector4f& a, const float b);

	//	Vector4f - float
	//	----------------
	Vector4f	operator-(const Vector4f& a, const float b);

	//	Vector4f x float
	//	----------------
	Vector4f	operator*(const Vector4f& a, const float b);

	//	Vector4f / float
	//	----------------
	Vector4f	operator/(const Vector4f& a, const float b);

}

#include "../../Inline/Maths/Vector4.inl"