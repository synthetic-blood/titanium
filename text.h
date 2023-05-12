#pragma once
#include<SDL_ttf.h>
#include<string>
#include<memory>
#include<sstream>
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
		titanium::texture t_texture;
		bool text_changed{ false };
		v2<> _text_box;
		void draw(SDL_Renderer* renderer)
		{
			if (text_changed)
			{
				t_texture.from_surface(renderer, _surface);

				set_texture(t_texture);

				text_changed = false;
			}
		}
	public:
		text(font& display_font, v2<> new_position) :
			object(new_position),
			_text_font(&display_font) {}
		void set_text(const std::string new_text)
		{
			_text_raw = new_text;
			_surface = TTF_RenderText_Blended(_text_font->_font, _text_raw.c_str(), { 255,255,255 });
			_text_box = { _surface->w,_surface->h };
			text_changed = true;
		}
		v2<int> get_size() const override
		{
			return _text_box * get_scale();
		}
	};
}