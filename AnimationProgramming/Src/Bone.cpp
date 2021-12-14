#include "../Include/Bone.h"

#include "../Engine.h"

Bone::Bone(size_t ID, Bone* parent)
	: ID(ID), parent(parent)
{

}

Mat4x4 Bone::GetLocalRestTransform()
{
	Vector3f position;
	Quaternion rotation;
	GetSkeletonBoneLocalBindTransform(ID, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Mat4x4 Bone::GetGlobalRestTransform()
{
	if (!parent)
		return localRestTransform;

	return parent->GetGlobalRestTransform() * localRestTransform;
}

Mat4x4 Bone::GetLocalAnimTransform(const char* animName, float frameTime, int keyFrameIndex, int nextKeyFrame)
{
	Vector3f curPosition;
	Quaternion curRotation;
	GetAnimLocalBoneTransform(animName, ID, keyFrameIndex, curPosition.x, curPosition.y, curPosition.z, curRotation.w, curRotation.x, curRotation.y, curRotation.z);

	Vector3f nextPosition;
	Quaternion nextRotation;
	GetAnimLocalBoneTransform(animName, ID, nextKeyFrame, nextPosition.x, nextPosition.y, nextPosition.z, nextRotation.w, nextRotation.x, nextRotation.y, nextRotation.z);

	Vector3f position = Maths::lerp(frameTime , curPosition, nextPosition);
	Quaternion rotation = Maths::Slerp(frameTime, curRotation, nextRotation);
	

	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Mat4x4 Bone::GetGlobalAnimTransform(const char* animName, float frameTime, int keyFrame, int nextKeyFrame)
{
	if (!parent)
		return localRestTransform * GetLocalAnimTransform(animName, frameTime, keyFrame, nextKeyFrame);

	return parent->GetGlobalAnimTransform(animName, frameTime, keyFrame, nextKeyFrame) * localRestTransform * GetLocalAnimTransform(animName, frameTime, keyFrame, nextKeyFrame);
}