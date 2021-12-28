#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

#include "../stdafx.h"

class Bone
{
private:
	Mat4x4 localRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransformInv = mat4x4Identity();
	Mat4x4 globalAnimTransform = mat4x4Identity();

	bool isDirty = true;

	Bone* parent = nullptr;

	size_t ID = -1;

	Mat4x4 GetLocalRestTransform();

	Mat4x4 GetGlobalRestTransform();

	Mat4x4 GetLocalAnimTransform(class AnimationInstance* enterAnimation, class AnimationInstance* exitAnimation, float crossfadeAlpha);

	Mat4x4 GetGlobalAnimTransform(class AnimationInstance* enterAnimation, class AnimationInstance* exitAnimation, float crossfadeAlpha);

public:
	Bone(size_t ID);

	void SetDirty() { isDirty = true; }

	Bone* GetParent() const { return parent; }

	void SetParent(Bone* newParent);

	void ComputeAnimTransform(AnimationInstance* enterAnimation, AnimationInstance* exitAnimation, float crossfadeAlpha);

	const Mat4x4& GetGlobalAnimTransform() const { return globalAnimTransform; }

	Mat4x4 GetBoneOffsetMatrix() const { return globalAnimTransform * globalRestTransformInv; }
};