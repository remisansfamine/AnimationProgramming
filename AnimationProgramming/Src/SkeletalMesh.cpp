#include "../Include/SkeletalMesh.h"

#include "../Engine.h"

void SkeletalMesh::Create()
{
	// Set skeleton bones
	for (size_t i = 0; i < GetSkeletonBoneCount() - 7; i++)
	{
		bones[i] = std::make_unique<Bone>(i);

		size_t parentID = GetSkeletonBoneParentIndex(i);

		if (parentID == -1)
			continue;

		Bone* bone = bones[i].get();

		bone->parent = bones[parentID].get();

		bone->localRestTransform = bone->GetLocalRestTransform();
		bone->globalRestTransform = bone->GetGlobalRestTransform();
	}
}

void SkeletalMesh::SetAnimation(const char* animationName)
{
	animName = animationName;
	keyCount = GetAnimKeyCount(animationName);
}

void SkeletalMesh::DrawWireframe(float frameTime, int key)
{
	float zOffset = -50.f;

	int animKey = key % keyCount;
	int nextKey = (key + 1) % keyCount;

	for (auto& [boneID, bone] : bones)
	{
		Bone* parent = bone->parent;

		if (!parent)
			continue;

		Vector3f currentPos = bone->GetGlobalAnimTransform(animName.c_str(), frameTime, animKey, nextKey).getPosition();
		Vector3f parentPos = parent->GetGlobalAnimTransform(animName.c_str(), frameTime, animKey, nextKey).getPosition();

		if (!parent->parent)
			DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 0, 1, 0);
		else
			DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 1, 0, 0);
	}

}