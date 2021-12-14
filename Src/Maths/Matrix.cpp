#include <iostream>

#include "../../Include/Maths/Matrix.h"


using namespace Maths;


/*========================    Matrix 4    =========================*/

Mat4x4  Maths::scale(const Vector3f scale)
{
    return {
        scale.x, 0.f, 0.f, 0.f,
        0.f, scale.y, 0.f, 0.f,
        0.f, 0.f, scale.z, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

//  Pitch rotation
Mat4x4  Maths::rotateX(const float angleRadians)
{
    float c = cosf(angleRadians);
    float s = sinf(angleRadians);

    //  Return 4x4 matrix
    return {
        1.f ,   0.f ,   0.f ,   0.f ,
        0.f ,   c   ,  -s   ,   0.f ,
        0.f ,   s   ,   c   ,   0.f ,
        0.f ,   0.f ,   0.f ,   1.f ,
    };
}

//  Yaw rotation
Mat4x4  Maths::rotateY(const float angleRadians)
{
    float c = cosf(angleRadians);
    float s = sinf(angleRadians);

    //  Return 4x4 matrix
    return {
        c   ,   0.f ,   s   ,   0.f ,
        0.f ,   1.f ,   0.f ,   0.f ,
       -s   ,   0.f ,   c   ,   0.f ,
        0.f ,   0.f ,   0.f ,   1.f ,
    };
}

//  Roll rotation
Mat4x4  Maths::rotateZ(const float angleRadians)
{
    float c = cosf(angleRadians);
    float s = sinf(angleRadians);


    //  Return 4x4 matrix
    return {
        c   ,  -s   ,   0.f ,   0.f ,
        s   ,   c   ,   0.f ,   0.f ,
        0.f ,   0.f ,   1.f ,   0.f ,
        0.f ,   0.f ,   0.f ,   1.f ,
    };
}

//  Translation
Mat4x4  Maths::translate(Vector3f a)
{
    //  Return 4x4 matrix
    return {
        1.f ,   0.f ,   0.f ,   a.x ,
        0.f ,   1.f ,   0.f ,   a.y ,
        0.f ,   0.f ,   1.f ,   a.z ,
        0.f ,   0.f ,   0.f ,   1.f ,
    };
}