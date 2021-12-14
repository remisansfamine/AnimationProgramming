// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

#include "../Include/Maths/Matrix.h"
#include "../Include/Maths/Quaternion.h"

Mat4x4 GetLocalTRS(const char* animName, int boneIndex, int keyFrameIndex)
{
	Vector3f position;
	Quaternion rotation;
	GetSkeletonBoneLocalBindTransform(boneIndex, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Mat4x4 GetGlobalBoneTransform(const char* animName, int boneIndex, int keyFrameIndex)
{
	int parentIndex = GetSkeletonBoneParentIndex(boneIndex);
	if (parentIndex == -1)
		return GetLocalTRS(animName, boneIndex, keyFrameIndex);

	return GetGlobalBoneTransform(animName, parentIndex, keyFrameIndex) * GetLocalTRS(animName, boneIndex, keyFrameIndex);
}

class CSimulation : public ISimulation
{
	int key = 0;

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
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		float zOffset = -50.f;

		for (int i = 0; i < GetSkeletonBoneCount() - 7; i++)
		{
			int spineParent = GetSkeletonBoneParentIndex(i);


			if (spineParent == -1)
				continue;

			Mat4x4 currentTR = GetGlobalBoneTransform("ThirdPersonWalk.anim", i, 0);
			Mat4x4 parentTR = GetGlobalBoneTransform("ThirdPersonWalk.anim", spineParent, 0);

			Vector3f currentPos = { currentTR.e[3], currentTR.e[7], currentTR.e[11] };
			Vector3f parentPos = { parentTR.e[3], parentTR.e[7], parentTR.e[11] };

			if (GetSkeletonBoneParentIndex(spineParent) == -1)
			 DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 0, 1, 0);
			else
				DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 1, 0, 0);
		}

		key = (key + 1) % GetAnimKeyCount("ThirdPersonWalk.anim");
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

