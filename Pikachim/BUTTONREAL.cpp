#include "stdafx.h"
#include "BUTTONREAL.h"

ButtonReal::ButtonReal(int x, int y, int w, int h, SDL_Renderer* screen, std::string path){
	rect_.x = x; 
	rect_.y = y; 
	rect_.w = w; 
	rect_.h = h; 
	status_ = 0;
	for (int i = 0; i < 3; i++)
		button_sprite_[i].setRect(rect_.x, rect_.y);
	loadFull(screen, path);
}

ButtonReal::~ButtonReal(){
	for (int i = 0; i < 3; i++)
		button_sprite_[i].Free();
	Free();
}

void ButtonReal::loadFull(SDL_Renderer* screen, std::string path){
	for (int i = 0; i < 3; i++){
		std::string temp = path;
		temp += ('0' + i);
		temp = temp + ".png";
		bool tam = button_sprite_[i].loadImage(temp, screen);
	}
}

bool ButtonReal::handle_events(SDL_Event m_event, Mix_Chunk* click_sound)
{
    int x = 0, y = 0;    
    if(m_event.type == SDL_MOUSEMOTION )// Event cua mouse
    {
		//Set rect cua mouse
        x = m_event.motion.x;
        y = m_event.motion.y;

        //If the mouse is over the button
        if (checkIfRectInsideButton(x, y) && status_ == 0)
        {
			status_ = 1;
        }
        else if ( (!checkIfRectInsideButton(x, y)) && status_ == 1)
        {
			status_ = 0;
        }    
    }
	//Click!!
    if(m_event.type == SDL_MOUSEBUTTONDOWN )
    {
		if(m_event.button.button == SDL_BUTTON_LEFT )// Chuot trai
        {
            x = m_event.button.x;
            y = m_event.button.y;
        
			//Click trung button
			if (checkIfRectInsideButton(x, y) && status_ != 2)
            {
				status_ = 2;
				Mix_PlayChannel(-1, click_sound, 0);
				return 1;
            }
        }
    }
	return 0;
}

bool ButtonReal::checkIfRectInsideButton(int x, int y){
	return ( ( x > rect_.x ) && ( x < rect_.x + rect_.w ) && ( y > rect_.y ) && ( y < rect_.y + rect_.h ) );
}

void ButtonReal::SHOW(SDL_Renderer* screen){
	button_sprite_[status_].Render(screen);
	if (status_ == 2){
		SDL_RenderPresent(screen);
		SDL_Delay(100);
	}
}