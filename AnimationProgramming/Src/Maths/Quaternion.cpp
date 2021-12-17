#include "../../Include/Maths/Quaternion.h"
#include "../../Include/Maths/Matrix.h"
#include "../../Include/Maths/Utils.h"


//  Constructors
//  ------------

Maths::Quaternion::Quaternion()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 0.f;
}

Maths::Quaternion::Quaternion(float in_x, float in_y, float in_z, float in_w)
{
    x = in_x;
    y = in_y;
    z = in_z;
    w = in_w;
}

Maths::Quaternion::Quaternion(Vector3f v, float in_w)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = in_w;
}

Maths::Quaternion::Quaternion(Vector4f v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

//  Internal Functions
//  ------------------

//  Functions
float Maths::Quaternion::length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float Maths::Quaternion::squareLength() const
{
    return x * x + y * y + z * z + w * w;
}

Maths::Quaternion Maths::Quaternion::normalized() const
{
    float len = length();
    float ilength = 1.0f / (len == 0 ? 1.f : len);

    return { x * ilength , y * ilength, z * ilength, w * ilength };
}

Maths::Quaternion Maths::Quaternion::invert() const
{
    float lenSq = squareLength();
    if (lenSq != 0.0)
    {
        float i = 1.0f / lenSq;
        return { x * -i, y * -i,z * -i,w * -i };
    }
    return *this;
}


void Maths::Quaternion::toAxisAngle(Vector3f& outAxis, float& outAngle)
{
    if (fabs(w) > 1.0f) *this = normalized();

    Vector3f resAxis = { 0.0f, 0.0f, 0.0f };
    float den = sqrtf(1.0f - w*w);

    if (den > 0.f)
    {
        resAxis.x = x/den;
        resAxis.y = y/den;
        resAxis.z = z/den;
    }
    else
    {
        // This occurs when the angle is zero.
        resAxis.x = 1.0f;
    }

    outAxis = resAxis;
    outAngle = 2.0f * acosf(w);
}

Maths::Vector3f Maths::Quaternion::toEuler()
{
    Vector3f angleDEG =
    { 
        atan2f(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y)),
        asinf(Maths::clamp(2.0f * (w * y - z * x), -1.f, 1.f)),
        atan2f(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z)) 
    };

    return angleDEG * DEG_TO_RAD;
}


// !! NOT VERIFIED YET
Maths::Mat4x4 Maths::Quaternion::toMatrix()
{
    Mat4x4 result = mat4x4Identity();

    float a2 = 2 * (x * x), b2 = 2 * (y * y), c2 = 2 * (z * z); //, d2=2*(w*w);

    float ab = 2 * (x * y), ac = 2 * (x * z), bc = 2 * (y * z);
    float ad = 2 * (x * w), bd = 2 * (y * w), cd = 2 * (z * w);

    result.e[0] = 1 - b2 - c2;
    result.e[1] = ab - cd;
    result.e[2] = ac + bd;

    result.e[4] = ab + cd;
    result.e[5] = 1 - a2 - c2;
    result.e[6] = bc - ad;

    result.e[8] = ac - bd;
    result.e[9] = bc + ad;
    result.e[10] = 1 - a2 - b2;

    return result;
}


//  External Functions (too heavy to be in .inl)
//  --------------------------------------------

Maths::Quaternion Maths::quaternionFromVector3ToVector3(Vector3f from, Vector3f to)
{
    Vector3f u = from.normalized();
    Vector3f v = to.normalized();

    if (u == -v)
    {
        return Quaternion(vector3Orthogonal(u).normalized(), 0.f);
    }

    Vector3f cross = vector3CrossProduct(from, to);
    
    return Quaternion(cross, 1.0f + dotProduct(from, to)).normalized();
}



Maths::Quaternion Maths::quaternionFromAxisAngle(const Vector3f& axis, float angle)
{
    return Quaternion(((axis.length() != 0.0f ? angle *= 0.5f : axis).normalized()) * sinf(angle), cosf(angle)).normalized();
}



Maths::Quaternion Maths::quaternionFromEuler(const float roll, const float pitch, const float yaw)
{
    float x0 = cosf(roll * 0.5f),   x1 = sinf(roll * 0.5f);
    float y0 = cosf(pitch * 0.5f),  y1 = sinf(pitch * 0.5f);
    float z0 = cosf(yaw * 0.5f),    z1 = sinf(yaw * 0.5f);

    return
    {
        x1 * y0 * z0 - x0 * y1 * z1,
        x0 * y1 * z0 + x1 * y0 * z1,
        x0 * y0 * z1 - x1 * y1 * z0,
        x0 * y0 * z0 + x1 * y1 * z1
    };
}



Maths::Quaternion Maths::quaternionFromEuler(const Vector3f& euler)
{
    return quaternionFromEuler(euler.x, euler.y, euler.z);
}


Maths::Quaternion Maths::operator*(const Quaternion& q, Mat4x4 mat)
{
    Quaternion to_return = { 1, 1, 1, 1 };

    for (int i = 0; i < 4; ++i)
    {
        float sum = 0.0f;
        for (int j = 0; j < 4; ++j)
            sum += q.e[j] * mat.c[j].e[i];
        to_return.e[i] = sum;
    }
    return to_return;
}

Maths::Vector3f Maths::vector3RotateByQuaternion(const Vector3f& v, const Quaternion& q)
{
    return
    {
        v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) + v.y * (2 * q.x * q.y - 2 * q.w * q.z) + v.z * (2 * q.x * q.z + 2 * q.w * q.y),
        v.x * (2 * q.w * q.z + 2 * q.x * q.y) + v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) + v.z * (-2 * q.w * q.x + 2 * q.y * q.z),
        v.x * (-2 * q.w * q.y + 2 * q.x * q.z) + v.y * (2 * q.w * q.x + 2 * q.y * q.z) + v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z)
    };
}

Maths::Vector3f Maths::Mat4x4::getPosition()
{
    return { e[3], e[7], e[11] };
}
