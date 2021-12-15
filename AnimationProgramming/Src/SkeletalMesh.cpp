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
		bone->globalRestTransformInv = invert(bone->GetGlobalRestTransform());
	}
}

void SkeletalMesh::SetAnimation(const char* animationName)
{
	currentAnimation = std::make_unique<Animation>(animationName);
}

void SkeletalMesh::DrawWireframe(float frameTime, int key)
{
	if (!currentAnimation)
		return;

	float zOffset = -50.f;

	int animKey = key % currentAnimation->frameCount;
	int nextKey = (key + 1) % currentAnimation->frameCount;

	for (auto& [boneID, bone] : bones)
	{
		Bone* parent = bone->parent;

		if (!parent)
			continue;

		Vector3f currentPos = bone->GetGlobalAnimTransform(currentAnimation.get(), frameTime, animKey, nextKey).getPosition();
		Vector3f parentPos = parent->GetGlobalAnimTransform(currentAnimation.get(), frameTime, animKey, nextKey).getPosition();

		if (!parent->parent)
			DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 0, 1, 0);
		else
			DrawLine(currentPos.x, currentPos.y + zOffset, currentPos.z, parentPos.x, parentPos.y + zOffset, parentPos.z, 1, 0, 0);
	}
}

void SkeletalMesh::Draw(float frameTime, int key)
{
	if (!currentAnimation)
		return;

	int animKey = key % currentAnimation->frameCount;
	int nextKey = (key + 1) % currentAnimation->frameCount;

	std::vector<Mat4x4> inversedMatrices;
	inversedMatrices.reserve((bones.size()));

	for (auto& [boneID, bone] : bones)
	{
		Mat4x4 finalMat = bone->GetGlobalAnimTransform(currentAnimation.get(), frameTime, animKey, nextKey) * bone->globalRestTransformInv;

		inversedMatrices.emplace_back(Maths::transpose(finalMat));
	}

	SetSkinningPose((const float*)inversedMatrices.data(), inversedMatrices.size());
}
