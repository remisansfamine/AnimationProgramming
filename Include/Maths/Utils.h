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
	T min(T a, T b);

	//	Return maximum value between two values
	//	Parameters : Type a, Type b
	//	---------------------------
	template<typename T>
	T max(T a, T b);

	//	Return a clamped value between two values
	//	Parameters : Type value, Type min, Type max
	//	-------------------------------------------
	template<typename T>
	T clamp(T value, T min, T max);

	//	Return a looped value between two values
	//	Parameters : Type value, Type min, Type max
	//	-------------------------------------------
	template<typename T>
	T loop(T value, T min, T max);

	//	Return a mapped value between two values
	//	Parameters : Type value, Type min1, Type max1, Type min2, Type max2
	//	-------------------------------------------------------------------
	template<typename T>
	T map(T value, T min1, T max1, T min2, T max2);

	//	Return a lerped value betwween two values
	//	Parameters : Type value, Type min, Type max,
	//	-------------------------------------------------------------------
	template <typename T>
	T lerp(T a, T x, T y);

	//	Switch boolean to its inverse
	//	Parameters : bool& a
	//	--------------------
	void switchBoolean(bool& a);
}

#include "../../Inline/Maths/Utils.inl"
