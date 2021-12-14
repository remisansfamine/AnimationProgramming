#pragma once

#include "../Include/Bone.h"

#include "../stdafx.h"

struct SkeletalMesh
{
	std::unordered_map<size_t, std::unique_ptr<Bone>> bones;

	void Create();
};
