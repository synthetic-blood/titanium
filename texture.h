#pragma once
#include<SDL_render.h>
#include<string>
#include<SDL_image.h>
#include"utils.h"
namespace titanium
{
	class texture
	{
		friend class window;
		friend class object;
	private:
		SDL_Texture* _raw_texture{ nullptr };
		SDL_Surface* _raw_surface{ nullptr };
		std::string _name;
		v2<int> _size;
		void load(SDL_Renderer* renderer)
		{
			_raw_texture = IMG_LoadTexture(renderer, _name.c_str());
		}
		void load_pending(SDL_Renderer* renderer)
		{
			_raw_texture = SDL_CreateTextureFromSurface(renderer, _raw_surface);
			_raw_surface = nullptr;
		}
		
	public:
		texture(const std::string name) :_name(name) {}
		texture() {}
		void operator=(texture& other) {
			_raw_texture = other._raw_texture;
		}
		void from_surface(SDL_Renderer* renderer)
		{
			_raw_texture = SDL_CreateTextureFromSurface(renderer, _raw_surface);
			SDL_FreeSurface(_raw_surface);
			_raw_surface = nullptr;
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
				SDL_QueryTexture(_raw_texture, 0, 0, &width, &height);
				return v2{ width,height };
			}
			else
			{
				return _size;
			}
		}
		~texture()
		{
			SDL_DestroyTexture(_raw_texture);
		}
	};
}