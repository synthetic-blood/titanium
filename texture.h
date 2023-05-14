#pragma once
#include<SDL_render.h>
#include<string>
#include<SDL_image.h>
#include"utils.h"
#include<optional>
namespace titanium
{
	class window;
	class texture
	{
		friend class window;
		friend class object;
	private:
		std::optional<SDL_Texture*> _raw_texture{ std::nullopt };
		std::optional<SDL_Surface*> _raw_surface{ std::nullopt };
		std::string _name;
		v2<int> _size;

		SDL_Color _color = { 255,255,255,255 };
	public:
		texture(const std::string name) :_name(name) {}
		texture() {}
		void load(window& renderer);
		void from_surface(SDL_Renderer* renderer)
		{
			_raw_texture = SDL_CreateTextureFromSurface(renderer, *_raw_surface);
			SDL_FreeSurface(*_raw_surface);
			_raw_surface.reset();
		}
		void set_pending(SDL_Surface* surface)
		{
			_raw_surface = surface;
			_size = { surface->w,surface->h };
		}
		v2<> get_texture_size() const
		{
			if (_raw_texture)
			{
				int width{ 0 };
				int height{ 0 };
				SDL_QueryTexture(*_raw_texture, 0, 0, &width, &height);
				return v2{ width,height };
			}
			else
			{
				return _size;
			}
		}
		~texture()
		{
			if (_raw_texture)
				SDL_DestroyTexture(*_raw_texture);
			if (_raw_surface)
				SDL_FreeSurface(*_raw_surface);
		}
	};
}
