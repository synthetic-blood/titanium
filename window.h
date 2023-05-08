#pragma once

#include<string>
#include<list>
#include<map>

#include<SDL_render.h>
#include<SDL_events.h>
#include<SDL_log.h>

#include"utils.h"
#include"text.h"

namespace titanium
{
	class text;
	class window
	{
	private:
		std::string _title;
		SDL_Window* _sdl_window{ nullptr };
		SDL_Renderer* _sdl_renderer{ nullptr };
		SDL_Event _event;
		v2 _render_position;
		std::map<SDL_Scancode,bool> _key_register;
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
			SDL_VideoInit(0);
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
		int counter = 0;
		void move_view(const int offset_x, const int offset_y)
		{
			_render_position.x += offset_x;
			_render_position.y += offset_y;
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
			counter = 0;
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
			counter++;
		}
		void draw_text(text &t)
		{
			t.draw(_sdl_renderer);
			SDL_Rect dst{ t.transform_to_rect() };
			SDL_RenderCopy(_sdl_renderer, t._texture, 0, &dst);
		}
		bool is_running() const
		{
			return _sdl_window != nullptr;
		}
	};
}