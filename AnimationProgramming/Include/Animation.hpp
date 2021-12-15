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

	size_t frameCount = 0u;

	Animation(const char* animation);
};