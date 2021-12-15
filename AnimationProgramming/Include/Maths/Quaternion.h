#pragma once

#include "Vector4.h"

namespace Maths
{
	union Mat4x4;
	union Quaternion
	{
		//	Variables
		//	---------
		float	 e[4];
		struct	 { float x; float y; float z; float w; };
		struct	 { float r; float g; float b; float a; };
		Vector4f vect4;

		//	Constructors
		//	------------
		Quaternion();
		Quaternion(float in_x, float in_y, float in_z, float in_w);
		Quaternion(Vector3f v, float in_w);
		Quaternion(Vector4f v);

		~Quaternion() {};

		//	Functions
		//	---------

		//	Return length of the quaternion
		//	Parameters : none
		//	-----------------
		float length() const;

		//	Return square length of the current quaternion
		//	Parameters : none
		//	-----------------
		float squareLength() const;

		//	Return the normalized current quaternion
		//	Parameters : none
		//	-----------------
		Quaternion normalized() const;

		//	Return the inverted current quaternion
		//	Parameters : none
		//	-----------------
		Quaternion invert() const;

		//	Convert the current quaternion to an Axis and an Angle
		//	Parameters : Vector3f& outAxis, float& outAngle
		//	-----------------------------------------------
		void	 toAxisAngle(Vector3f& outAxis, float& outAngle);

		//	Convert the current quaternion to an euler Vector3f
		//	Parameters : none
		//	-----------------
		Vector3f toEuler();

		//	Convert the current quaternion to a Mat4x4
		//	Parameters : none
		//	-----------------
		Mat4x4	 toMatrix();
	};

	//	Return a Quaternion identity
	//	Parameters : none
	//	-----------------
	Quaternion quaternionIdentity();

	//	Lerp a Quaternion from a quaternion to another quaternion
	//	Parameters : Quaternion q1, Quaternion q2, float amount
	//	-------------------------------------------------------
	Quaternion quaternionLerp(Quaternion q1, Quaternion q2, float amount);

	//	Lerp a  Quaternion from a quaternion to another quaternion, then normalize the result
	//	Parameters : Quaternion q1, Quaternion q2, float amount
	//	-------------------------------------------------------
	Quaternion quaternionNormalizedlerp(Quaternion q1, Quaternion q2, float amount);

	//	Return a quaternion from the angle between two vectors
	//	Parameters : Vector3f from, Vector3f to
	//	---------------------------------------
	Quaternion quaternionFromVector3ToVector3(Vector3f from, Vector3f to);

	//	Return a quaternion from an Axis and an angle
	//	Parameters : Vector3f axis, float angle
	//	---------------------------------------
	Quaternion quaternionFromAxisAngle(const Vector3f& axis, float angle);

	//	Return a quaternion from an Euler
	//	Parameters : const float roll, const float pitch, const float yaw
	//	-----------------------------------------------------------------
	Quaternion quaternionFromEuler(const float roll, const float pitch, const float yaw);

	//	Return a quaternion from an Euler Vector3f
	//	Parameters : const Vector3f& euler
	//	----------------------------------
	Quaternion quaternionFromEuler(const Vector3f& euler);

	//	Return a rotated Vector3f from a Quaternion
	//	Parameters : const Vector3f& v, const Quaternion& q
	//	---------------------------------------------------
	Vector3f vector3RotateByQuaternion(const Vector3f& v, const Quaternion& q);

	//	Operators
	//	---------

	//	Quaternion + Quaternion
	//	-----------------------
	Quaternion operator+(const Quaternion& q1, const Quaternion& q2);

	//	Quaternion - Quaternion
	//	-----------------------
	Quaternion operator-(const Quaternion& q1, const Quaternion& q2);

	//	Quaternion x Quaternion
	//	-----------------------
	Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

	//	Quaternion / Quaternion
	//	-----------------------
	Quaternion operator/(const Quaternion& q1, const Quaternion& q2);


	//	Quaternion + float
	//	------------------
	Quaternion operator+(const Quaternion& q, float value);

	//	Quaternion - float
	//	------------------
	Quaternion operator-(const Quaternion& q, float value);

	//	Quaternion x float
	//	------------------
	Quaternion operator*(const Quaternion& q, float value);

	Quaternion operator*(float value, const Quaternion& q);

	//	Quaternion x Mat4x4
	//	-------------------
	Quaternion operator*(const Quaternion& q, Mat4x4 mat);

	Quaternion slerp(float lambda, const Quaternion& a, const Quaternion& b);
}

#include "../../Inline/Maths/Quaternion.inl"