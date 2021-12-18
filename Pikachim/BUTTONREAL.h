#ifndef BUTTON_REAL_H
#define BUTTON_REAL_H
#include "BaseObject.h"
#include "MakeButton.h"

class ButtonReal : public BaseObject{
public:
	ButtonReal(int x, int y, int w, int h, SDL_Renderer* screen, std::string path);
	~ButtonReal();
	bool handle_events(SDL_Event m_event, Mix_Chunk* click_sound);
	bool checkIfRectInsideButton(int x, int y);
	void loadFull(SDL_Renderer* screen, std::string path);
	void SHOW(SDL_Renderer* screen);

	BaseObject button_sprite_[3];
	int status_;
};

#endif