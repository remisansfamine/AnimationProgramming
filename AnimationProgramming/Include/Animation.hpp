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

	int currentKeyFrame = 0;
	int nextKeyFrame = 0;

	float frame = 0.f;
	float timeScale = 1.f;

	float speed = 30.f;
	float duration = 1.f;

	Animation(const char* animation, float speed);

	void SetFrame(float deltaTime);

	Transform& GetCurrentBoneTransform(size_t boneID);
	Transform& GetNextBoneTransform(size_t boneID);
};