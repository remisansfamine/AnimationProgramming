#pragma once

#include "../stdafx.h"

#include "../Include/Transform.h"

struct KeyFrame
{
	std::vector<Transform> palette;

	const Transform& GetBoneTransform(size_t boneID) const { return palette[boneID]; }
};

class Animation
{
private:
	size_t frameCount = 1u;

	std::string name;

	std::vector<KeyFrame> keyFrames;

public:
	Animation(const char* animation);

	size_t GetFrameCount() const { return frameCount; }

	std::string GetName() const { return name; }

	const KeyFrame& GetKeyFrameAt(size_t keyCount) const { return keyFrames[keyCount]; }
};

struct AnimationInstance
{
private:
	std::shared_ptr<Animation> animation;

	int currentKeyFrame = 0;
	int nextKeyFrame = 0;

	float frame = 0.f;

	float speed = 30.f;

	bool evenFrameCount = false;

public:
	float timeScale = 1.f;
	float duration = 1.f;

	AnimationInstance(std::shared_ptr<Animation> animation, float speed);

	void SetFrame(float deltaTime);

	void DrawTimeline(const Vector3f& offset = Vector3f::zero()) const;

	const Transform& GetCurrentBoneTransform(size_t boneID) const;
	const Transform& GetNextBoneTransform(size_t boneID) const;

	Transform GetBlendedBoneTransform(size_t boneID) const;
};