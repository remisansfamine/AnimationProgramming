#include "../Include/Bone.h"

#include "../Engine.h"

#include "../Include/Animation.hpp"

Bone::Bone(size_t ID)
	: ID(ID)
{
	localRestTransform = GetLocalRestTransform();
}

void Bone::SetParent(Bone* newParent)
{
	parent = newParent;

	if (!newParent)
	{
		globalRestTransform = globalRestTransformInv = mat4x4Identity();
		return;
	}

	globalRestTransform = GetGlobalRestTransform();
	globalRestTransformInv = invert(globalRestTransform);
}

Mat4x4 Bone::GetLocalRestTransform()
{
	Transform localTransform;
	GetSkeletonBoneLocalBindTransform(ID,
									  localTransform.position.x, localTransform.position.y, localTransform.position.z,
									  localTransform.rotation.w, localTransform.rotation.x, localTransform.rotation.y, localTransform.rotation.z);

	return localTransform.getMatrix();
}

Mat4x4 Bone::GetGlobalRestTransform()
{
	if (!isDirty)
		return globalRestTransform;

	if (!parent)
		globalRestTransform = localRestTransform;
	else 
		globalRestTransform = parent->GetGlobalRestTransform() * localRestTransform;

	isDirty = false;

	return globalRestTransform;
}

Mat4x4 Bone::GetLocalAnimTransform(Animation* enterAnimation, Animation* exitAnimation, float crossfadeAlpha)
{
	Transform& enterCurrTransform = enterAnimation->GetCurrentBoneTransform(ID);
	Transform& enterNextTransform = enterAnimation->GetNextBoneTransform(ID);

	Transform enterTransform = Transform::blend(fabsf(enterAnimation->frame), enterCurrTransform, enterNextTransform);

	if (!exitAnimation)
		return enterTransform.getMatrix();

	Transform& exitCurrTransform = exitAnimation->GetCurrentBoneTransform(ID);
	Transform& exitNextTransform = exitAnimation->GetNextBoneTransform(ID);

	Transform exitTransform = Transform::blend(fabsf(exitAnimation->frame), exitCurrTransform, exitNextTransform);

	return Transform::blend(crossfadeAlpha, exitTransform, enterTransform).getMatrix();
}

Mat4x4 Bone::GetGlobalAnimTransform(Animation* enterAnimation, Animation* exitAnimation, float crossfadeAlpha)
{
	if (!isDirty)
		return globalAnimTransform;

	Mat4x4 localAnim = localRestTransform * GetLocalAnimTransform(enterAnimation, exitAnimation, crossfadeAlpha);

	if (!parent)
		globalAnimTransform = localAnim;
	else
		globalAnimTransform = parent->GetGlobalAnimTransform(enterAnimation, exitAnimation, crossfadeAlpha) * localAnim;

	isDirty = false;

	return globalAnimTransform;
}