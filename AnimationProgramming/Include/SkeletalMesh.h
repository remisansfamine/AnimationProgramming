#pragma once

#include "../Include/Bone.h"

#include "../stdafx.h"

#include "../Include/Animation.hpp"

class SkeletalMesh
{
private:
	std::unordered_map<size_t, std::unique_ptr<Bone>> bones;

	Bone* root = nullptr;

	std::string animName;
	size_t keyCount = 0u;

	float crossfadeDuration = 1.f;
	float currentCrossfadeTime = 0.f;
	float crossfadeAlpha = 0.f;
	float normalizedTimeScale = 1.f;

	void ResetCrossfade();

public:
	std::unique_ptr<AnimationInstance> enterAnimation = nullptr;
	std::unique_ptr<AnimationInstance> exitAnimation = nullptr;

	void Create();

	void SetAnimation(std::shared_ptr<Animation>, float speed, float newCrossfadeDuration);

	void Update(float deltaTime);

	void DrawWireframe(const Vector3f& offset = Vector3f::zero()) const;

	void DrawMesh(const Vector3f& offset = Vector3f::zero()) const;

};
