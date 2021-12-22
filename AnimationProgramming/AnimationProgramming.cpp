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

	std::shared_ptr<Animation> tposeAnim;
	std::shared_ptr<Animation> walkAnim;
	std::shared_ptr<Animation> runAnim;

	virtual void Init() override
	{
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		tposeAnim = std::make_shared<Animation>(nullptr);
		walkAnim = std::make_shared<Animation>("ThirdPersonWalk.anim");
		runAnim = std::make_shared<Animation>("ThirdPersonRun.anim");

		skeleton.Create();

		skeleton.SetAnimation(tposeAnim, 30.f, 0.1f);
	}
		int animCount = 0;

	virtual void Update(float frameTime) override
	{
		// Gizmo
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		frame += frameTime;

		skeleton.Update(frameTime);

		skeleton.DrawMesh(Vector3f(0.f, 50.f, 0.f));
		skeleton.DrawWireframe(Vector3f(0.f, -50.f, 0.f));

		if (frame >= 5.f && animCount < 1)
		{
			skeleton.SetAnimation(runAnim, -30.f, 0.3f);
			animCount++;
		}
		else if (frame >= 10.f && animCount < 2)
		{
			skeleton.SetAnimation(tposeAnim, 30.f, 0.3f);
			animCount++;
		}
		else if (frame >= 15.f && animCount < 3)
		{
			skeleton.SetAnimation(walkAnim, 30.f, 0.3f);
			animCount = 0;
			frame = 0.f;
		}
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

