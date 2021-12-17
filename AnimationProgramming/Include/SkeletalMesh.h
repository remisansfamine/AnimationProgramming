#pragma once

#include "../Include/Bone.h"

#include "../stdafx.h"

#include "../Include/Animation.hpp"

struct SkeletalMesh
{
	std::unordered_map<size_t, std::unique_ptr<Bone>> bones;

	Bone* root = nullptr;

	std::string animName;
	size_t keyCount = 0u;

	float crossfadeDuration = 1.f;
	float currentCrossfadeTime = 0.f;
	float crossfadeAlpha = 0.f;
	float normalizedTimeScale = 1.f;

	void Create();

	void SetAnimation(const char* animationName, float speed, float newCrossfadeDuration);

	void ResetCrossfade();
	void Update(float deltaTime);

	void DrawWireframe(const Vector3f& offset = Vector3f::zero());

	void DrawMesh(const Vector3f& offset = Vector3f::zero());

	std::unique_ptr<Animation> enterAnimation = nullptr;
	std::unique_ptr<Animation> exitAnimation = nullptr;
};
