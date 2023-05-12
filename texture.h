#pragma once
#include<SDL_render.h>
#include<string>
#include<SDL_image.h>
namespace titanium
{
	class texture
	{
		friend class window;
		friend class object;
	private:
		SDL_Texture* _raw_texture{ nullptr };
		std::string _name;
		void load(SDL_Renderer* renderer)
		{
			_raw_texture = IMG_LoadTexture(renderer, _name.c_str());
		}
	public:
		texture(const std::string name) :_name(name) {}
		texture() {}
		void operator=(texture& other) {
			_raw_texture = other._raw_texture;
		}
		v2<> get_texture_size() const
		{
			int width;
			int height;
			SDL_QueryTexture(_raw_texture, 0, 0, &width, &height);
			return v2{ width,height };
		}
		~texture()
		{
			SDL_DestroyTexture(_raw_texture);
		}
	};
}