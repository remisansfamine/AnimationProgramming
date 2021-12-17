
namespace Maths
{

	template<typename T>
	T min(const T& a, const T& b)
	{
		return (a > b) ? b : a;
	}

	template<typename T>
	T max(const T& a, const T& b)
	{
		return (a > b) ? a : b;
	}

	template<typename T>
	T clamp(const T& value, const T& min, const T& max)
	{
		if (value > max) return max;
		if (value < min) return min;
		
		return value;
	}
	template<typename T>
	T map(const T& value, const T& min1, const T& max1, const T& min2, const T& max2)
	{
		return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
	}

	template <typename T, typename S>
	T lerp(S a, const T& x, const T& y)
	{
		return x * (S(1) - a) + y * a;
	}

	template <typename T>
	T loop(const T& in, const T& min, const T& max)
	{
		if (in > max) return min;
		if (in < min) return max;

		return in;
	}

	template <typename T>
	char sign(const T& val)
	{
		return (T(0) < val) - (val < T(0));
	}
}