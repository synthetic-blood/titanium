
#pragma once
#include<SDL_pixels.h>
#include"utils.h"
#include"texture.h"
#include<optional>
namespace titanium
{
	class object
	{
		friend class text;
		friend class window;
	private:
		v2<float> _position;
		v2<float> _scale;
		v2<float> _pivot;
		v2<> _size;
		object* _parent{ nullptr};
		std::shared_ptr<texture> _texture = std::make_shared<texture>();
	public:
		v2<int> virtual get_size() const
		{
			return _texture->get_texture_size() * _scale;
		}
		std::string name;
		void set_pivot(v2<float> new_pivot)
		{
			_pivot = new_pivot;
		}
		v2<float> get_pivot() const
		{
			return _pivot;
		}
		SDL_Rect transform_to_rect()
		{
			return SDL_Rect{ static_cast<int>(get_position().x),static_cast<int>(get_position().y),get_size().x,get_size().y };
		}

		v2<float> get_absolute_position() const
		{
			return _position;
		}
		v2<float> get_position() const
		{
			return get_absolute_position() + (
				_parent ? _parent->get_position() : v2<float>{ 0, 0 }
			);
		}

		void set_position(const v2<float> position)
		{
			_position = position - (get_size() * _pivot);
		}

		void set_parent(object* parent)
		{
			_parent = parent;
			place_at(*parent, _pivot);//set_position(parent->get_absolute_position() + (get_size() * _pivot));
		}
		const std::optional<object*> get_parent()
		{
			return _parent;
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
		void set_scale(v2<float> new_scale)
		{
			_scale = new_scale;
		}
		object(const v2 <float> inital_position = { 0,0 }, const v2<float> initial_scale = { 1.f,1.f }, const v2<float> initial_pivot = { 0,0 }) :
			_position(inital_position),
			_scale(initial_scale),
			_pivot(initial_pivot) { }
		void move(const v2<float> offset)
		{
			_position = _position + offset;
		}
		void move(const object& target, const float step)
		{
			double angle{ std::atan2(target.get_absolute_position().y - get_absolute_position().y,target.get_absolute_position().x - get_absolute_position().x) };
			const v2<float>offset{ std::cos(angle) * step, std::sin(angle) * step };
			move(offset);
		}
		void set_texture(std::shared_ptr<texture>& desired_texture)
		{
			_texture = desired_texture;
		}
		void place_at(const object& other, const v2<float> pivot = { 0,0 }, std::optional<v2<float>> from = std::nullopt, float time_factor = 1.f)
		{
			set_position((from ? from->lerp(other.get_absolute_position(), time_factor) : other.get_absolute_position()) + (other.get_size() * pivot));
		}
	};
}