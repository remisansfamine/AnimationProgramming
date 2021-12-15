#pragma once

#include "../Include/Bone.h"

#include "../stdafx.h"

#include "../Include/Animation.hpp"

struct SkeletalMesh
{
	std::unordered_map<size_t, std::unique_ptr<Bone>> bones;

	std::string animName;
	size_t keyCount = 0u;

	void Create();

	void SetAnimation(const char* animationName);

	void DrawWireframe(float frameTime, int key);

	void Draw(float frameTime, int key);

	std::unique_ptr<Animation> currentAnimation = nullptr;
};
