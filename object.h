
#pragma once
#include<SDL_pixels.h>
#include"utils.h"
#include"texture.h"
#include<optional>
namespace titanium
{
	class object
	{
		friend class window;
	private:
		v2<> _position;
		v2<float> _scale;
		v2<float> _pivot;
		v2<> _size;
		std::optional<object*> _parent{ std::nullopt };
		texture _texture;
		v2<int> get_size() const
		{
			return _texture.get_texture_size() * _scale;
		}
	public:
		std::string name;
		void set_pivot(v2<float> new_pivot)
		{
			_pivot = new_pivot;
		}
		SDL_Rect transform_to_rect()
		{
			return SDL_Rect{ get_position().x,get_position().y,(int)_scale.x,(int)_scale.y };
		}

		v2<> get_absolute_position() const
		{
			return _position;
		}
		v2<> get_position() const
		{
			return get_absolute_position() + (
				_parent ? _parent.value()->get_position() : v2{ 0, 0 }
			);
		}

		void set_position(const v2<> position)
		{
			_position = position + (get_size() * _pivot);
		}

		void set_parent(object* parent)
		{
			_parent = parent;
		}
		v2<float> get_scale() const
		{
			return _scale;
		}
		void scale(const float factor)
		{
			_scale.x *= factor;
			_scale.y *= factor;
		}
		object(const v2<> inital_position = { 0,0 }, const v2<float> initial_scale = { 1.f,1.f }, const v2<float> initial_pivot = { 0,0 }) :
			_position(inital_position),
			_scale(initial_scale),
			_pivot(initial_pivot) { }
		void move(int offset_x, int offset_y)
		{
			_position = _position + v2{ offset_x,offset_y };
		}
		void set_texture(texture& desired_texture)
		{
			_texture = desired_texture;
		}
		void place_at(const object& other, const v2<float> pivot = { 0,0 })
		{
			set_position(other.get_position() + (get_size() * pivot));
		}
	};
}