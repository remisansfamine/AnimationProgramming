#include "../Include/Animation.hpp"

#include "../Engine.h"

Animation::Animation(const char* animationName)
{
	size_t boneCount = GetSkeletonBoneCount() - 7;

	if (animationName)
	{
		name = animationName;

		frameCount = GetAnimKeyCount(animationName);
		keyFrames.reserve(frameCount);

		for (size_t i = 0u; i < frameCount; i++)
		{
			KeyFrame keyFrame;

			keyFrame.palette.reserve(boneCount);

			for (size_t boneID = 0u; boneID < boneCount; boneID++)
			{
				Transform bone;

				GetAnimLocalBoneTransform(animationName, boneID, i, bone.position.x, bone.position.y, bone.position.z, bone.rotation.w, bone.rotation.x, bone.rotation.y, bone.rotation.z);

				keyFrame.palette.emplace_back(bone);
			}

			keyFrames.emplace_back(keyFrame);
		}
	}
	else
	{
		KeyFrame keyFrame;

		keyFrame.palette.reserve(boneCount);

		for (size_t boneID = 0u; boneID < boneCount; boneID++)
			keyFrame.palette.emplace_back(Transform());

		keyFrames.emplace_back(keyFrame);
	}
}

AnimationInstance::AnimationInstance(std::shared_ptr<Animation> animation, float speed)
	: speed(speed), animation(animation)
{
	if (animation->frameCount > 1u)
		duration = (float)animation->frameCount / fabsf(speed);
}

void AnimationInstance::SetFrame(float deltaTime)
{
	frame += deltaTime * timeScale * speed;

	if (fabsf(frame) < 1.f)
		return;

	frame = 0.f;

	currentKeyFrame = loop(currentKeyFrame + sign(speed), 0, (int)animation->frameCount - 1);
	nextKeyFrame = loop(currentKeyFrame + sign(speed), 0, (int)animation->frameCount - 1);
}

Transform& AnimationInstance::GetCurrentBoneTransform(size_t boneID)
{
	return animation->keyFrames[currentKeyFrame].palette[boneID];
}

Transform& AnimationInstance::GetNextBoneTransform(size_t boneID)
{
	return animation->keyFrames[nextKeyFrame].palette[boneID];
}

Transform AnimationInstance::GetBlendedBoneTransform(size_t boneID)
{
	return Transform::blend(fabsf(frame), GetCurrentBoneTransform(boneID), GetNextBoneTransform(boneID));
}