#pragma once

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

#include "../stdafx.h"

struct Bone
{
	Bone* parent = nullptr;

	size_t ID = -1;

	Bone(size_t ID, Bone* parent = nullptr);

	Mat4x4 localRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransform = mat4x4Identity();
	Mat4x4 globalRestTransformInv = mat4x4Identity();

	Mat4x4 GetLocalRestTransform();

	Mat4x4 GetGlobalRestTransform();

	Mat4x4 GetLocalAnimTransform(const char* animName, float frameTime, int keyFrame, int nextKeyFrame);

	Mat4x4 GetGlobalAnimTransform(const char* animName, float frameTime, int keyFrame, int nextKeyFrame);

	void Compute(std::vector<Mat4x4>& inversedMatrix, const Mat4x4& parentMat, const char* animName, float frameTime, int keyFrame, int nextKeyFrame);
};