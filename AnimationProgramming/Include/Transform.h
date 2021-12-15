#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

struct Transform
{
	Vector3f position;
	Quaternion rotation;

	static Transform blend(float lambda, const Transform& a, const Transform& b);

	Mat4x4 getMatrix();
};
