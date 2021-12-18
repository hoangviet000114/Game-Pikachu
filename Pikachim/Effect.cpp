#include "stdafx.h"
#include "Effect.h"

void Effect::loadEffect(SDL_Renderer* screen, std::string path, int num_of_sprite){
	for (int i = 0; i < num_of_sprite; i++){
		std::string temp = path;
		temp += ('0' + i);
		temp = temp + ".png";
		bool tam = effect_sprite_[i].loadImage(temp, screen);
	}
}

void Effect::showEffect(SDL_Renderer* screen, int effect_code, NODE_ rect_effect){
	effect_sprite_[effect_code].setRect(rect_effect.x, rect_effect.y);
	effect_sprite_[effect_code].Render(screen);
}