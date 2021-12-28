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

		Vector3f getPosition() const;
	};

	//	Mat4x4 Functions
	//	----------------


	//	Return Mat4x4 Identity
	//	Parameters : none
	//	----------------------
	Mat4x4 mat4x4Identity();

	Mat4x4 translate(const Vector3f& a);

	Mat4x4 transpose(const Mat4x4& in);

	Mat4x4 invert(const Mat4x4& in);

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


