#include "../Include/Bone.h"

#include "../Engine.h"

Mat4x4 Bone::GetLocalRestTRS()
{
	Vector3f position;
	Quaternion rotation;
	GetSkeletonBoneLocalBindTransform(ID, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Mat4x4 Bone::GetGlobalRestTRS()
{
	if (!parent)
		return localRestTransform;

	return parent->GetGlobalRestTRS() * localRestTransform;
}

Mat4x4 Bone::GetLocalTRS(const char* animName, int keyFrameIndex)
{
	Vector3f position;
	Quaternion rotation;
	GetAnimLocalBoneTransform(animName, ID, keyFrameIndex, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Mat4x4 Bone::GetGlobalBoneTransform(const char* animName, int keyFrameIndex)
{
	if (!parent)
		return localRestTransform * GetLocalTRS(animName, keyFrameIndex);

	return parent->GetGlobalBoneTransform(animName, keyFrameIndex) * localRestTransform * GetLocalTRS(animName, keyFrameIndex);
}