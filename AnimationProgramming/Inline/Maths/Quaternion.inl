#include <cmath>

using namespace Maths;

/*========================    Quaternion    ========================*/


inline Maths::Quaternion Maths::quaternionIdentity()
{
    return { 0.0f, 0.0f, 0.0f, 1.0f };
}


inline Maths::Quaternion Maths::operator+(const Quaternion& q1, const Quaternion& q2)
{
    return { q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w };
}


inline Maths::Quaternion Maths::operator+(const Quaternion& q, float value)
{
    return { q.x + value, q.y + value, q.z + value, q.w + value };
}




inline Maths::Quaternion Maths::operator-(const Quaternion& q1, const Quaternion& q2)
{
    return { q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w };
}

inline Maths::Quaternion Maths::operator-(const Quaternion& q, float value)
{
    return { q.x - value, q.y - value, q.z - value, q.w - value };
}




inline Maths::Quaternion Maths::operator*(const Quaternion& q1, const Quaternion& q2)
{
    return
    {
        q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y,
        q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z,
        q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
    };
}


inline Maths::Quaternion Maths::operator*(const Quaternion& q, float value)
{
    return { q.x * value, q.y * value, q.z * value, q.w * value };
}

inline Maths::Quaternion Maths::operator*(float value, const Quaternion& q)
{
    return { q.x * value, q.y * value, q.z * value, q.w * value };
}

inline Maths::Quaternion Maths::operator/(const Quaternion& q1, const Quaternion& q2)
{
    return { q1.x / q2.x, q1.y / q2.y, q1.z / q2.z, q1.w / q2.w };
}



inline Maths::Quaternion Maths::quaternionLerp(Quaternion q1, Quaternion q2, float amount)
{
    return
    {
        q1.x + amount * (q2.x - q1.x),
        q1.y + amount * (q2.y - q1.y),
        q1.z + amount * (q2.z - q1.z),
        q1.w + amount * (q2.w - q1.w)
    };
}

inline Maths::Quaternion Maths::quaternionNormalizedlerp(Quaternion q1, Quaternion q2, float amount)
{
    return quaternionLerp(q1, q2, amount).normalized();
}

inline Maths::Quaternion Maths::Slerp(float lambda, const Quaternion& a, const Quaternion& b)
{
    float cosHalfTheta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

    float sign = cosHalfTheta < 0.f ? -1.f : 1.f;

    cosHalfTheta = fabsf(cosHalfTheta);

    if (cosHalfTheta >= 1.0f)
        return a;

    float halfTheta = acosf(cosHalfTheta);
    float oneOverSinHalfTheta = 1.f / sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

    float phi = lambda * halfTheta;

    float ratioA = sinf(halfTheta - phi) * oneOverSinHalfTheta;
    float ratioB = sinf(phi) * oneOverSinHalfTheta * sign;

    return a * ratioA + b * ratioB;
}