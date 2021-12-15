#include "../Include/Animation.hpp"

#include "../Engine.h"

Animation::Animation(const char* animationName)
	: name(animationName)
{
	frameCount = GetAnimKeyCount(animationName);

	size_t boneCount = GetSkeletonBoneCount() - 7;

	for (size_t i = 0u; i < frameCount; i++)
	{
		KeyFrame keyFrame;

		for (size_t boneID = 0u; boneID < boneCount; boneID++)
		{
			Transform bone;

			GetAnimLocalBoneTransform(animationName, boneID, i, bone.position.x, bone.position.y, bone.position.z, bone.rotation.w, bone.rotation.x, bone.rotation.y, bone.rotation.z);

			keyFrame.palette.push_back(bone);
		}

		keyFrames.push_back(keyFrame);
	}
}
