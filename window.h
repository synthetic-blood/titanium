#pragma once

#include<string>
#include<list>
#include<map>

#include<SDL_render.h>
#include<SDL_events.h>
#include<SDL_log.h>

#include"utils.h"
#include"text.h"
#include"texture.h"
namespace titanium
{
	class text;
	class window
	{
		friend class texture;
	private:
		std::string _title;
		SDL_Window* _sdl_window{ nullptr };
		SDL_Renderer* _sdl_renderer{ nullptr };
		SDL_Event _event;
		std::map<SDL_Scancode, bool> _key_register;
		void destroy()
		{
			SDL_DestroyWindow(_sdl_window);
			SDL_DestroyRenderer(_sdl_renderer);
			_sdl_window = nullptr;
			_sdl_renderer = nullptr;
		}
	public:
		window(const std::string title) :_title(title)
		{
			SDL_Init(SDL_INIT_EVERYTHING);
			_sdl_window = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				1200, 600, 0);
			if (is_running())
			{
				_sdl_renderer = SDL_CreateRenderer(_sdl_window, -1, 0);
			}
		}
		bool is_running() const
		{
			return _sdl_window != nullptr;
		}
		void render()
		{
			while (SDL_PollEvent(&_event))
			{
				switch (_event.type)
				{
				case SDL_QUIT:
					destroy();
					break;
				case SDL_KEYUP:
					_key_register[_event.key.keysym.scancode] = false;
					break;
				}
			}

			SDL_RenderPresent(_sdl_renderer);
			SDL_SetRenderDrawColor(_sdl_renderer, 0, 0, 0, 0);
			SDL_RenderClear(_sdl_renderer);
		}
		bool key_pressed(const SDL_Scancode code)
		{
			const Uint8* state{ SDL_GetKeyboardState(0) };
			if (!_key_register[code])
			{
				if (state[code])
				{
					_key_register[code] = true;
				}
				return state[code];
			}
			return false;
		}
		void draw_rect(object& rectangle, const SDL_Color color)
		{
			SDL_Rect rect{ rectangle.transform_to_rect() };
			SDL_SetRenderDrawColor(_sdl_renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(_sdl_renderer, &rect);
		}
		void test()
		{
			//SDL_Surface* surface = SDL_CreateRGBSurface(0, 600, 100, 24, 0xff0000, 0x00ff00, 0x0000ff, 0);
			//SDL_Rect rect = { 0, 0, surface->w, surface->h };
			//SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0));

			SDL_Surface* surface = SDL_CreateRGBSurface(0, 600, 100, 24, 0xff0000, 0x00ff00, 0x0000ff, 0);
			Uint32 red = SDL_MapRGB(surface->format, 255, 0, 0);
			SDL_FillRect(surface, NULL, red);

			SDL_Texture* texture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);

			SDL_Rect dst = { 0,0,surface->w,surface->h };
			SDL_RenderCopy(_sdl_renderer, texture, 0, &dst);
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surface);
		}
		void draw_texture(object& obj, SDL_Color color = { 255,255,255, 255 }, SDL_BlendMode mode = SDL_BLENDMODE_BLEND)
		{
			if (obj._texture->_raw_surface)
				obj._texture->from_surface(_sdl_renderer);
			if (obj._texture->_raw_texture)
			{
				//if (color.a != 255)
					SDL_SetTextureAlphaMod(*obj._texture->_raw_texture, color.a);
				//if (color.r != 255 && color.g != 255 && color.b != 255)
					SDL_SetTextureColorMod(*obj._texture->_raw_texture, color.r, color.g, color.b);
				//if (mode != SDL_BLENDMODE_BLEND)
					SDL_SetTextureBlendMode(*obj._texture->_raw_texture, mode);
				SDL_Rect dst{ obj.transform_to_rect() };
				SDL_RenderCopy(_sdl_renderer, *obj._texture->_raw_texture, 0, &dst);
			}
		}
	};
	void titanium::texture::load(titanium::window& renderer)
	{
		_raw_texture = IMG_LoadTexture(renderer._sdl_renderer, _name.c_str());
	}
}