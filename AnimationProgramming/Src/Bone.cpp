#include "../Include/Bone.h"

#include "../Engine.h"

#include "../Include/Animation.hpp"

Bone::Bone(size_t ID, Bone* parent)
	: ID(ID), parent(parent)
{

}

Mat4x4 Bone::GetLocalRestTransform()
{
	Transform localTransform;
	GetSkeletonBoneLocalBindTransform(ID,
									  localTransform.position.x, localTransform.position.y, localTransform.position.z,
									  localTransform.rotation.w, localTransform.rotation.x, localTransform.rotation.y, localTransform.rotation.z);

	return localTransform.getMatrix();
}

Mat4x4 Bone::GetGlobalRestTransform()
{
	if (!parent)
		return localRestTransform;

	return parent->GetGlobalRestTransform() * localRestTransform;
}

Mat4x4 Bone::GetLocalAnimTransform(Animation* animation, float frameTime, int keyFrameIndex, int nextKeyFrame)
{
	Transform& currentTransform = animation->keyFrames[keyFrameIndex].palette[ID];
	Transform& nextTransform = animation->keyFrames[nextKeyFrame].palette[ID];

	return Transform::blend(frameTime, currentTransform, nextTransform).getMatrix();
}

Mat4x4 Bone::GetGlobalAnimTransform(Animation* animation, float frameTime, int keyFrame, int nextKeyFrame)
{
	if (!parent)
		return localRestTransform * GetLocalAnimTransform(animation, frameTime, keyFrame, nextKeyFrame);

	return parent->GetGlobalAnimTransform(animation, frameTime, keyFrame, nextKeyFrame) * localRestTransform * GetLocalAnimTransform(animation, frameTime, keyFrame, nextKeyFrame);
}