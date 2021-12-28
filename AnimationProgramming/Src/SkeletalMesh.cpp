#include "../Include/SkeletalMesh.h"

#include "../Engine.h"

void SkeletalMesh::Create()
{
	// Set skeleton bones
	for (size_t i = 0; i < GetSkeletonBoneCount() - 7; i++)
	{
		bones[i] = std::make_unique<Bone>(i);
		Bone* bone = bones[i].get();

		size_t parentID = GetSkeletonBoneParentIndex(i);

		if (parentID == -1)
		{
			root = bone;
			continue;
		}

		Bone* parent = bones[parentID].get();

		bone->SetParent(parent);
	}
}

void SkeletalMesh::SetAnimation(std::shared_ptr<Animation> newAnimation, float speed, float newCrossfadeDuration)
{
	crossfadeDuration = newCrossfadeDuration;

	if (enterAnimation)
	{
		exitAnimation = nullptr;
		exitAnimation = std::move(enterAnimation);
	}

	enterAnimation = std::make_unique<AnimationInstance>(newAnimation, speed);

	if (exitAnimation)
		normalizedTimeScale = enterAnimation->duration / exitAnimation->duration;
}

void SkeletalMesh::ResetCrossfade()
{
	currentCrossfadeTime = 0.f;
	crossfadeAlpha = 0.f;
	crossfadeDuration = 0.f;

	exitAnimation = nullptr;

	normalizedTimeScale = 1.f;
	enterAnimation->timeScale = 1.f;
}

void SkeletalMesh::Update(float deltaTime)
{
	if (exitAnimation)
	{
		currentCrossfadeTime += deltaTime;

		if (currentCrossfadeTime > crossfadeDuration)
		{
			ResetCrossfade();
		}
		else
		{
			crossfadeAlpha = currentCrossfadeTime / crossfadeDuration;

			enterAnimation->timeScale = lerp(crossfadeAlpha, normalizedTimeScale, 1.f);
			exitAnimation->SetFrame(deltaTime);
		}
	}

	enterAnimation->SetFrame(deltaTime);

	for (auto& [boneID, bone] : bones)
		bone->SetDirty();

	for (auto& [boneID, bone] : bones)
		bone->ComputeAnimTransform(enterAnimation.get(), exitAnimation.get(), crossfadeAlpha);
}

void SkeletalMesh::DrawWireframe(const Vector3f& offset) const
{
	for (auto& [boneID, bone] : bones)
	{
		Bone* parent = bone->GetParent();

		if (!parent)
			continue;

		Vector3f currentPos = bone->GetGlobalAnimTransform().getPosition() + offset;
		Vector3f parentPos = parent->GetGlobalAnimTransform().getPosition() + offset;

		bool isRoot = parent == root;

		DrawLine(currentPos.x, currentPos.y, currentPos.z, parentPos.x, parentPos.y, parentPos.z, !isRoot, isRoot, 0);
	}
}

void SkeletalMesh::DrawMesh(const Vector3f& offset) const
{
	std::vector<Mat4x4> inversedMatrices;
	inversedMatrices.reserve(bones.size());

	for (auto& [boneID, bone] : bones)
		inversedMatrices.emplace_back(Maths::transpose(translate(offset) * bone->GetBoneOffsetMatrix()));

	SetSkinningPose((const float*)inversedMatrices.data(), inversedMatrices.size());
}
