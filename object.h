
#pragma once
#include<SDL_pixels.h>
#include"utils.h"
namespace titanium
{
	class object
	{
	private:
		v2 _position;
		v2 _size;
		object* _parent{ nullptr };
		bool is_valid{ false };
	public:
		std::string name;
		SDL_Rect transform_to_rect()
		{
			return SDL_Rect{ get_position().x,get_position().y,_size.x,_size.y };
		}
		v2 get_position() const
		{
			return _position + (is_valid ? _parent->get_position() : v2{ 0, 0 });
		}
		void set_parent(object* parent)
		{
			is_valid = true;
			_parent = parent;
			SDL_Log("%d", _parent->get_position().x);
		}
		v2 get_size() const
		{
			return _size;
		}

		void set_size(const v2 new_size)
		{
			_size = new_size;
		}

		object(const v2 inital_position = { 0,0 }, const v2 initial_size = { 0,0 }) :
			_position(inital_position),
			_size(initial_size) {
		}
		void move(int offset_x, int offset_y)
		{
			_position = _position + v2{ offset_x,offset_y };
		}
	};
}