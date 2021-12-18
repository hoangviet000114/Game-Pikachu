#include "stdafx.h"
#include "MakeButton.h"

void Button::setInfomation( int x, int y, int w, int h){
	rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;
	status_ = 1;
}

bool Button::checkButton(int x, int y){
	return ( ( x > rect_.x ) && ( x < rect_.x + rect_.w ) && ( y > rect_.y ) && ( y < rect_.y + rect_.h ) );
}

bool Button::handle_events(SDL_Event m_event)
{
    int x = 0, y = 0;    
    if(m_event.type == SDL_MOUSEMOTION )// Event cua mouse
    {
		//Set rect cua mouse
        x = m_event.motion.x;
        y = m_event.motion.y;

        //If the mouse is over the button
        if (checkButton(x, y) && status_ == 1)
        {
			status_ = 2;
        }
        else if ( (!checkButton(x, y)) && status_ == 2)
        {
			status_ = 1;
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
			if (checkButton(x, y) && status_ != 3)
            {
				status_ = 3;
				return 1;
            }
        }
    }
	return 0;
}