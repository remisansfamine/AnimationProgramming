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

    }

    inline float determinant(const Mat4x4& in)
    {

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
