
namespace Maths
{

	template<typename T>
	T min(T a, T b)
	{
		return (a > b) ? b : a;
	}

	template<typename T>
	T max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template<typename T>
	T clamp(T value, T min, T max)
	{
		if (value > max) return max;
		if (value < min) return min;
		
		return value;
	}

	template<typename T>
	T loop(T value, T min, T max)
	{
		if (value > max) return min;
		if (value < min) return max;
		
		return value;
	}

	template<typename T>
	T map(T value, T min1, T max1, T min2, T max2)
	{
		return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
	}

	template <typename T>
	T lerp(T a, T x, T y)
	{
		return x * (1 - a) + y * a;
	}

	inline void switchBoolean(bool& a)
	{
		a = !a;
	}


}