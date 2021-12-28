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
	if (animation->GetFrameCount() > 1u)
		duration = (float)animation->GetFrameCount() / fabsf(speed);

	if (animation->GetFrameCount() % 2 == 0)
		evenFrameCount = true;
}

void AnimationInstance::SetFrame(float deltaTime)
{
	frame += deltaTime * timeScale * speed;

	if (fabsf(frame) < 1.f)
		return;

	frame = 0.f;

	currentKeyFrame = loop(currentKeyFrame + sign(speed), 0, (int)animation->GetFrameCount() - 1);
	nextKeyFrame = loop(currentKeyFrame + sign(speed), 0, (int)animation->GetFrameCount() - 1);
}

void AnimationInstance::DrawTimeline(const Vector3f& offset) const
{
	Vector3f lineTopPosition = Vector3f::zero();
	float space = 5.f;

	lineTopPosition = offset - Vector3f::xAxis() * (1 / timeScale) * ((animation->GetFrameCount() * 0.5f) * space + (int)evenFrameCount * space * 0.5f);

	if (animation->GetFrameCount() == 1u)
	{
		DrawLine(lineTopPosition.x - 15.f, lineTopPosition.y, lineTopPosition.z, lineTopPosition.x + 15.f, lineTopPosition.y, lineTopPosition.z, 0.2f, 0.2f, 0.2f);
		return;
	}

	for (size_t i = 0u; i < animation->GetFrameCount(); ++i)
	{
		if (i == currentKeyFrame)
		{
			for (int j = -5; j <= 5; j++)
			{
				DrawLine(lineTopPosition.x + j * 0.1f, lineTopPosition.y, lineTopPosition.z + 0.5f, lineTopPosition.x + j * 0.1f, lineTopPosition.y, lineTopPosition.z - 11.f, 1.f, 0.f, 0.f);
			}
		}
		else
			DrawLine(lineTopPosition.x, lineTopPosition.y, lineTopPosition.z, lineTopPosition.x, lineTopPosition.y, lineTopPosition.z - 10.f, 0.2f, 0.2f, 0.2f);
		lineTopPosition = lineTopPosition + Vector3f::xAxis() * (1 / timeScale) * space;
	}

}

const Transform& AnimationInstance::GetCurrentBoneTransform(size_t boneID) const
{
	return animation->GetKeyFrameAt(currentKeyFrame).GetBoneTransform(boneID);
}

const Transform& AnimationInstance::GetNextBoneTransform(size_t boneID) const
{
	return animation->GetKeyFrameAt(nextKeyFrame).GetBoneTransform(boneID);
}

Transform AnimationInstance::GetBlendedBoneTransform(size_t boneID) const
{
	return Transform::blend(fabsf(frame), GetCurrentBoneTransform(boneID), GetNextBoneTransform(boneID));
}