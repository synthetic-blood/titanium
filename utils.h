#pragma once
#include<SDL_rect.h>
namespace titanium
{
	struct v2
	{
		int x{ 0 };
		int y{ 0 };
		v2 operator+(const v2 other) const
		{
			return v2{ x + other.x,y + other.y };
		}
	};
}