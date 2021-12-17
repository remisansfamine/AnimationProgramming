#include <iostream>

#include "../../Include/Maths/Matrix.h"

namespace Maths
{
    /*========================    Matrix 4    =========================*/

    //  Translation
    Mat4x4 translate(const Vector3f& in)
    {
        //  Return 4x4 matrix
        return {
            1.f ,   0.f ,   0.f ,   in.x,
            0.f ,   1.f ,   0.f ,   in.y,
            0.f ,   0.f ,   1.f ,   in.z,
            0.f ,   0.f ,   0.f ,   1.f ,
        };
    }
}
