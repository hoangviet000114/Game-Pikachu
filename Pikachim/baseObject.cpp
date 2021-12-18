#include "stdafx.h"
#include "baseObject.h"

BaseObject::BaseObject(){
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject(){
	Free();
}

bool BaseObject::loadImage(std::string path, SDL_Renderer* screen){// Load xong object se co thong tin ve texture va rect
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	//Bay gio can dua toan bo surface vao texture
	if (load_surface != NULL){
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, CL_KEY_R, CL_KEY_G, CL_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL){//Chuyen thong tin sang texture thanh cong !!
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);//Giai phong cai surface vi khong can nua
	}

	p_object_ = new_texture;
	return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip){ //Ve anh len des
	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RenderCopy(des, p_object_, clip, &renderquad); 
}

void BaseObject::Free(){
	if (p_object_ != NULL){
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}