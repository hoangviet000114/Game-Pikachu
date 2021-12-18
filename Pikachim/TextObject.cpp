#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject(int x, int y){
	rect_.x = x;
	rect_.y = y;
}

TextObject::~TextObject(){
	;
}

void TextObject::setColor(const int& type){
	if (type == RED_TEXT){
		SDL_Color color = {255, 0, 0};
		text_color_ = color;
	}
	else if (type == WHITE_TEXT){
		SDL_Color color = {255, 255, 255};
		text_color_ = color;
	}
	else{
		SDL_Color color = {0, 0, 0};
		text_color_ = color;
	}
}

void TextObject::createGameText(TTF_Font* font, SDL_Renderer* des){

	SDL_Surface* surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	p_object_ = SDL_CreateTextureFromSurface(des, surface);
	SDL_FreeSurface(surface);
	TTF_SizeText(font, str_val_.c_str(), &rect_.w, &rect_.h);
	Render(des);
}

void TextObject::drawText(SDL_Renderer* des, const SDL_Rect* clip){
	SDL_RenderCopy(des, p_object_, clip, &rect_);
}