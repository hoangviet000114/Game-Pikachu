#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "Common.h"
#include "BaseObject.h"

class Button : public BaseObject{
public:
	int status_;
	Button(){;}
	~Button(){;}
	void setInfomation(int x, int y, int w, int h);
	bool handle_events(SDL_Event m_event);
	bool checkButton(int x, int y);
};

#endif