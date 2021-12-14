#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

struct Bone
{
	Bone* parent = nullptr;
	size_t ID = -1;

	Bone(size_t ID) : ID(ID) { }

	Mat4x4 localRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransform = mat4x4Identity();

	Mat4x4 GetLocalRestTRS();

	Mat4x4 GetGlobalRestTRS();
};