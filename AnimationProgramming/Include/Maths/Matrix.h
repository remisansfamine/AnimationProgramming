#pragma once

#include <cmath>
#include "Vector4.h"

namespace Maths
{
	union Quaternion;

	union Mat4x4
	{
		//	Constructor / Destructor
		//	------------------------
		Mat4x4() = default;
		~Mat4x4() {};

		//	Variables
		//	---------
		float e[16];
		Vector4f c[4];

		//	Functions
		//	---------

		//	Return a quaternion from the current Matrix
		//	Parameters : none
		//	-----------------
		Quaternion toQuaternion();
		Vector3f getPosition();
	};

	//	Mat4x4 Functions
	//	----------------


	//	Return Mat4x4 Identity
	//	Parameters : none
	//	----------------------
	Mat4x4 mat4x4Identity();

	//	Return a scaled Mat4x
	//	Parameters : const Vector3f scale
	//	--------------------------------- 
	Mat4x4 scale(const Vector3f& scale);

	Mat4x4 translate(const Vector3f& a);

	//	Operators
	//	---------

	//	float x mat4x4 
	Mat4x4 operator*(const float& a, const Mat4x4& b);

	//  Mat4x4 x float4
	Vector4f operator*(const Mat4x4& m, const Vector4f& v);

	//  mat4x4 x mat4x4
	Mat4x4 operator*(const Mat4x4& a, const Mat4x4& b);

	//  Mat4x4 + Mat4x4
	Mat4x4 operator+(const Mat4x4& a, const Mat4x4& b);
}

#include "../../Inline/Maths/Matrix.inl"


