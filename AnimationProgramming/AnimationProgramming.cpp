// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

#include "../Include/SkeletalMesh.h"

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

class CSimulation : public ISimulation
{
	int key = 0;
	float frame = 0.f;

	SkeletalMesh skeleton;

	virtual void Init() override
	{
		system("PAUSE");

		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		skeleton.Create();

		skeleton.SetAnimation("ThirdPersonWalk.anim");
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		skeleton.DrawWireframe(frame, key);

		frame += frameTime;

		if (frame < 1.f)
			return;

		frame = 0.f;

		key++;
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

