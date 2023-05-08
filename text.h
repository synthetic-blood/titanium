#pragma once
#include<SDL_ttf.h>
#include<string>
#include<memory>

#include"object.h"

namespace titanium
{
	class font
	{
		friend class text;
	private:
		TTF_Font* _font{ nullptr };
	public:
		font(std::string name)
		{
			if (TTF_WasInit() == 0) TTF_Init();

			_font = TTF_OpenFont(name.append(".ttf").c_str(), 32);

			if (_font == nullptr)
				exit(1);
			else
			{
				SDL_Log("[font] loaded %s", name.c_str());
			}
		}
		~font()
		{
			TTF_CloseFont(_font);
		}
	};

	class text :public object {
		friend class window;
	private:
		font* _text_font;
		std::string _text_raw;
		SDL_Surface* _surface{ nullptr };
		SDL_Texture* _texture{ nullptr };
		bool text_changed{ false };

		SDL_Texture* draw(SDL_Renderer* renderer)
		{
			if (text_changed)
			{
				SDL_DestroyTexture(_texture);
				_texture = SDL_CreateTextureFromSurface(renderer, _surface);
				SDL_FreeSurface(_surface);
				text_changed = false;
			}
			return _texture;
		}
		void regenerate_box()
		{
			set_size({ _surface->w,_surface->h });
		}
	public:
		text(font& display_font, v2 new_position) :
			object(new_position, { 0,0 }),
			_text_font(&display_font) {}
		void set_text(const std::string new_text)
		{
			_text_raw = new_text;
			_surface = TTF_RenderText_Blended(_text_font->_font, _text_raw.c_str(), { 255,255,255,255 });
			regenerate_box();
			text_changed = true;
		}
	};
}