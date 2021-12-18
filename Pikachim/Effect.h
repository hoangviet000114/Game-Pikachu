#ifndef EFFECT_
#define EFFECT_

#include "Common.h"
#include "BaseObject.h"

class Effect{
public:
	Effect(){;}
	~Effect(){;}
	void loadEffect(SDL_Renderer* screen, std::string path, int num_of_sprite);
	void showEffect(SDL_Renderer* screen, int effect_code, NODE_ rect_effect);

	BaseObject effect_sprite_[10];
};

#endif