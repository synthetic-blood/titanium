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

			_font = TTF_OpenFont(name.c_str(), 64);

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
		bool text_changed{ false };
	public:
		text(font& display_font, v2<float> new_position) :
			object(new_position),
			_text_font(&display_font) {}
		void set_text(const std::string new_text)
		{
			_text_raw = new_text;
			_texture->set_pending(TTF_RenderText_Blended(_text_font->_font, _text_raw.c_str(), { 255,255,255 }));
		}
		v2<int> get_size() const override
		{
			return _texture->get_texture_size() * get_scale();
		}
	};
}