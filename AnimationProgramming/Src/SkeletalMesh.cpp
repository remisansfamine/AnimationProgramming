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

		bone->localRestTransform = bone->GetLocalRestTRS();
		bone->globalRestTransform = bone->GetGlobalRestTRS();
	}
}
