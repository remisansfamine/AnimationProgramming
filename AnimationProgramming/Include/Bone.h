#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

#include "../stdafx.h"

struct Bone
{
	Mat4x4 localRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransformInv = mat4x4Identity();
	Mat4x4 globalAnimTransform = mat4x4Identity();

	bool isDirty = true;

	Bone* parent = nullptr;

	size_t ID = -1;

	Bone(size_t ID);

	void SetParent(Bone* newParent);

	Mat4x4 GetLocalRestTransform();

	Mat4x4 GetGlobalRestTransform();

	Mat4x4 GetLocalAnimTransform(class Animation* enterAnimation, class Animation* exitAnimation, float crossfadeAlpha);

	Mat4x4 GetGlobalAnimTransform(class Animation* enterAnimation, class Animation* exitAnimation, float crossfadeAlpha);

};