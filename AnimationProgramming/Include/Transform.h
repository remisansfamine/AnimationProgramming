#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

struct Transform
{
	Vector3f position = Vector3f::zero();
	Quaternion rotation = quaternionIdentity();

	static Transform blend(float lambda, const Transform& a, const Transform& b);

	Mat4x4 getMatrix();
};
