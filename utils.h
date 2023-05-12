#pragma once
#include<SDL_rect.h>
namespace titanium
{
	template <typename T = int>struct v2
	{
		T x{ 0 };
		T y{ 0 };
		template<typename U>
		v2 operator+(const v2<U> other) const
		{
			return v2{ x + static_cast<T>(other.x), y + static_cast<T>(other.y) };
		}
		template<typename U>
		v2 operator*(const v2<U> other) const
		{
			return v2{ static_cast<T>(x * other.x), static_cast<T>(y * other.y) };
		}
		v2 operator/(int other)
		{
			return { x / other,y / other };
		}
	};
}