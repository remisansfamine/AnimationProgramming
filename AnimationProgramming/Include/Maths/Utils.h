#pragma once

#define PI		3.14159265358979323846f
#define TAU		PI * 2.0f
#define HALF_PI PI / 2.0f

#define RAD_TO_DEG (180.0f/PI)
#define DEG_TO_RAD (PI/180.0f)

namespace Maths
{
	//	Return minimum value between two values
	//	Parameters : Type a, Type b
	//	---------------------------
	template<typename T>
	T min(const T& a, const T& b);

	//	Return maximum value between two values
	//	Parameters : Type a, Type b
	//	---------------------------
	template<typename T>
	T max(const T& a, const T& b);

	//	Return a clamped value between two values
	//	Parameters : Type value, Type min, Type max
	//	-------------------------------------------
	template<typename T>
	T clamp(const T& value, const T& min, const T& max);

	//	Return a mapped value between two values
	//	Parameters : Type value, Type min1, Type max1, Type min2, Type max2
	//	-------------------------------------------------------------------
	template<typename T>
	T map(const T& value, const T& min1, const T& max1, const T& min2, const T& max2);

	//	Return a lerped value betwween two values
	//	Parameters : Type value, Type min, Type max,
	//	-------------------------------------------------------------------
	template <typename T, typename S>
	T lerp(S a, const T& x, const T& y);

	template <typename T>
	T loop(const T& in, const T& min, const T& max);

	template <typename T>
	char sign(const T& val);
}

#include "../../Inline/Maths/Utils.inl"
