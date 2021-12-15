#include "../Include/Transform.h"

Mat4x4 Transform::getMatrix()
{
	Mat4x4 translation = Maths::translate(Vector3f(position));
	Mat4x4 rotMat = rotation.toMatrix();

	return translation * rotMat;
}

Transform Transform::blend(float lambda, const Transform& a, const Transform& b)
{
	Vector3f position = Maths::lerp(lambda, a.position, b.position);
	Quaternion rotation = Maths::slerp(lambda, a.rotation, b.rotation);

	return { position, rotation };
}
