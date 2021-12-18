#ifndef text_object_h
#define text_object_h
#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

#include <iostream>
using namespace std;

class TextObject : public BaseObject{
public:
	enum TextColor{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	TextObject(int x, int y);
	~TextObject();

	void setText(const std::string& text) {str_val_ = text;}
	void setColor(const int& type);
	void createGameText(TTF_Font* font, SDL_Renderer* des);
	void drawText(SDL_Renderer* des, const SDL_Rect* clip = NULL);
//private:
	std::string str_val_;
	SDL_Color text_color_;
};

#endif