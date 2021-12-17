namespace Maths
{
    //====================================== Matrix Functions ======================================

    inline Mat4x4 mat4x4Identity()
    {
        return {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f,
        };
    }

    inline Mat4x4 transpose(const Mat4x4& in)
    {
        return
        {
            in.e[0], in.e[4], in.e[8] , in.e[12],
            in.e[1], in.e[5], in.e[9] , in.e[13],
            in.e[2], in.e[6], in.e[10], in.e[14],
            in.e[3], in.e[7], in.e[11], in.e[15]
        };
    }

    inline Mat4x4 invert(const Mat4x4& in)
    {
        Mat4x4 result = { 0 };

        // Cache the matrix values (speed optimization)
        float a00 = in.e[0],  a01 = in.e[1],  a02 = in.e[2],  a03 = in.e[3];
        float a10 = in.e[4],  a11 = in.e[5],  a12 = in.e[6],  a13 = in.e[7];
        float a20 = in.e[8],  a21 = in.e[9],  a22 = in.e[10], a23 = in.e[11];
        float a30 = in.e[12], a31 = in.e[13], a32 = in.e[14], a33 = in.e[15];

        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        float det = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

        result.e[0]  = (a11 * b11 - a12 * b10 + a13 * b09);
        result.e[1]  = (-a01 * b11 + a02 * b10 - a03 * b09);
        result.e[2]  = (a31 * b05 - a32 * b04 + a33 * b03);
        result.e[3]  = (-a21 * b05 + a22 * b04 - a23 * b03);
        result.e[4]  = (-a10 * b11 + a12 * b08 - a13 * b07);
        result.e[5]  = (a00 * b11 - a02 * b08 + a03 * b07);
        result.e[6]  = (-a30 * b05 + a32 * b02 - a33 * b01);
        result.e[7]  = (a20 * b05 - a22 * b02 + a23 * b01);
        result.e[8]  = (a10 * b10 - a11 * b08 + a13 * b06);
        result.e[9]  = (-a00 * b10 + a01 * b08 - a03 * b06);
        result.e[10] = (a30 * b04 - a31 * b02 + a33 * b00);
        result.e[11] = (-a20 * b04 + a21 * b02 - a23 * b00);
        result.e[12] = (-a10 * b09 + a11 * b07 - a12 * b06);
        result.e[13] = (a00 * b09 - a01 * b07 + a02 * b06);
        result.e[14] = (-a30 * b03 + a31 * b01 - a32 * b00);
        result.e[15] = (a20 * b03 - a21 * b01 + a22 * b00);

        return (1.0f / det) * result;
    }

    inline Mat4x4 operator*(const float& a, const Mat4x4& b)
    {
        Mat4x4 to_return = mat4x4Identity();

        for (int i = 0; i < 16; i++)
        {
            to_return.e[i] = b.e[i] * a;
        }

        return to_return;
    }

    //  Mat4x4 x Vector4f
    inline Vector4f operator*(const Mat4x4& m, const Vector4f& v)
    {
        Vector4f result;

        for (int i = 0; i < 4; i++)
        {
            float sum = 0.f;
            for (int j = 0; j < 4; j++)
                sum += m.c[i].e[j] * v.e[j];

            result.e[i] = sum;
        }

        return result;
    }

    //  Mat4x4 x Mat4x4
    inline Mat4x4 operator*(const Mat4x4& a, const Mat4x4& b)
    {
        Mat4x4 result = { 0.f };

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0.f;
                for (int k = 0; k < 4; k++)
                    sum += a.c[i].e[k] * b.c[k].e[j];

                result.c[i].e[j] = sum;
            }
        }

        return result;
    }

    inline Mat4x4 operator+(const Mat4x4& a, const Mat4x4& b)
    {
        Mat4x4 mat = { };
        for (int col = 0; col < 4; col++)
            for (int row = 0; row < 4; row++)
                    mat.c[col].e[row] += a.c[col].e[row] + b.c[col].e[row];
        return mat;
    }
}
