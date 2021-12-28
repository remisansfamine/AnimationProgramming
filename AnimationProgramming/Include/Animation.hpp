#pragma once

#include "../stdafx.h"

#include "../Include/Transform.h"

struct KeyFrame
{
	std::vector<Transform> palette;
};

class Animation
{
public:
	std::vector<KeyFrame> keyFrames;

	std::string name;

	size_t frameCount = 1u;

	Animation(const char* animation);
};

struct AnimationInstance
{
	AnimationInstance(std::shared_ptr<Animation> animation, float speed);

	std::shared_ptr<Animation> animation;

	int currentKeyFrame = 0;
	int nextKeyFrame = 0;

	float frame = 0.f;
	float timeScale = 1.f;

	float speed = 30.f;
	float duration = 1.f;

	bool evenFrameCount = false;

	void SetFrame(float deltaTime);

	void DrawTimeline(const Vector3f& offset = Vector3f::zero());

	Transform& GetCurrentBoneTransform(size_t boneID);
	Transform& GetNextBoneTransform(size_t boneID);

	Transform GetBlendedBoneTransform(size_t boneID);
};