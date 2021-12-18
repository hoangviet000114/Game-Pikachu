#include "stdafx.h"
#include "Common.h"
#include "BaseObject.h"
#include "TileMap.h"
#include "TextObject.h"
#include "BUTTONREAL.h"
#include "Effect.h"

BaseObject g_background, g_background_win, g_menu, g_lose, g_win_end_game;
Effect g_clock_destroyed_effect;

bool InitData(){
	bool success = 1;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) return 0;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Pikachim make by DoubleV", 
								 SDL_WINDOWPOS_UNDEFINED, 
								 SDL_WINDOWPOS_UNDEFINED, 
								 SCREEN_WIDTH, 
								 SCREEN_HEIGHT, 
								 SDL_WINDOW_SHOWN);

	if (g_window == NULL)
		return 0;
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			return 0;
		else{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); //Mau cua nen trong
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = 0;
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		success = false;

	music = Mix_LoadMUS("Sounddd//background_music.mp3");
	if (music == NULL){
		return false;
	}
	click_sound = Mix_LoadWAV("Sounddd//click.WAV");
	if (click_sound == NULL){
		return false;
	}
	fail_click_sound = Mix_LoadWAV("Sounddd//failClick.wav");
	if (fail_click_sound == NULL){
		return false;
	}
	clock_destroyed_sound = Mix_LoadWAV("Sounddd//ClockBoooom.wav");
	if (clock_destroyed_sound == NULL){
		return false;
	}
	win_sound = Mix_LoadWAV("Sounddd//YouWonAMap.mp3");
	if (win_sound == NULL){
		return false;
	}
	loser_sound = Mix_LoadMUS("Sounddd//bokeu.mp3");
	if (loser_sound == NULL){
		return false;
	}
	victory_sound = Mix_LoadWAV("Sounddd//Victory.wav");
	if (victory_sound == NULL){
		return false;
	}

	if (TTF_Init() < 0){
		SDL_Log("%s", TTF_GetError());
		return false;
	}

	return success;
}

bool LoadBackground(){
	bool ret = g_background.loadImage("sprite//background.png", g_screen);
	ret = min(g_background_win.loadImage("sprite//backgroundWIN.png", g_screen), ret);
	return ret;
}

bool loadMenu(){
	bool ret = g_menu.loadImage("sprite//Menu.png", g_screen);
	return ret;
}

bool loadLoseScreen(){
	bool ret = g_lose.loadImage("sprite//LOSE_BG.png", g_screen);
	return ret;
}

bool loadWinScreen(){
	bool ret = g_win_end_game.loadImage("sprite//WIN_BG.png", g_screen);
	return ret;
}

void DoWhenYouClearAMap(){
	Mix_PlayChannel(-1, clock_destroyed_sound, 0);
	Mix_PlayChannel(-1, win_sound, 0);

	for (int i = 0; i < NUM_OF_CLOCK_EFFECT_SPRITE; i++){
		SDL_RenderClear(g_screen);
		g_background_win.Render(g_screen, NULL);
		g_clock_destroyed_effect.showEffect(g_screen, i, makeNode(CLOCK_EFFECT_RECT_X, CLOCK_EFFECT_RECT_Y));
		SDL_RenderPresent(g_screen);
		SDL_Delay(TIME_DELAY_SPRITE_EFFECT);
	}
	SDL_RenderClear(g_screen);
	g_background_win.Render(g_screen, NULL);
	SDL_RenderPresent(g_screen);
	SDL_Delay(1000);
}

void close(){//Don dep tat ca
	g_background.Free();
	g_background_win.Free();
	g_menu.Free();
	g_lose.Free();
	g_lose.Free();
	g_win_end_game.Free();
	
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;
	///////////////////////////////////
	Mix_FreeMusic(music);
	Mix_FreeMusic(loser_sound);

	Mix_FreeChunk(victory_sound);
	Mix_FreeChunk(click_sound);
	Mix_FreeChunk(fail_click_sound);
	Mix_FreeChunk(clock_destroyed_sound);
	Mix_FreeChunk(win_sound);
	
	Mix_CloseAudio();
	///////////////////////////////////
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

int main(int argc, char* argv[])
{
	////////////////////////////////////////////LOADEVERYTHING/////////////////////////////////////////////
	if (InitData() == false)
		return -1;
	if (loadMenu() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;
	if (loadLoseScreen() == false)
		return -1;
	if (loadWinScreen() == false)
		return -1;
	g_clock_destroyed_effect.loadEffect(g_screen, "EffectClock/", NUM_OF_CLOCK_EFFECT_SPRITE);

	TTF_Font* font = NULL;
	font = TTF_OpenFont("FONTT.ttf", FONTSIZE);
	TextObject dem_nguoc(TIME_RECT_X, TIME_RECT_Y);
	TextObject level_text(LEVEL_TEXT_RECT_X, LEVEL_TEXT_RECT_Y);
	std::string TEXT;
	//////////////////////////////////OK!! NOW WE WILL PLAY THIS GAME <3 ///////////////////////////////////
	bool is_quit = false;
	while (is_quit == false){
		/////////////////////////////////////////////////////MENUUUUUUUU//////////////////////////////////////////////////////
		
		ButtonReal play_button(PLAY_RECT_X, PLAY_RECT_Y, PLAY_SIZE_H, PLAY_SIZE_W, g_screen, "sprite/PLAY");
		bool is_play = false;
		Mix_PlayMusic(music, -1);
		while (is_play == false){
			bool is_mouse = false;
			while (SDL_PollEvent(&g_event) != 0){
				if (g_event.type == SDL_QUIT){
					return 0;
				}
				else 
					is_mouse = true;
			}

			//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);//Set mau
			SDL_RenderClear(g_screen);// Clear man hinh
			g_menu.Render(g_screen, NULL);

			if (is_mouse == true)
				is_play = play_button.handle_events(g_event, click_sound);
			play_button.SHOW(g_screen);
		
			SDL_RenderPresent(g_screen);
		}
		Mix_HaltMusic();
		play_button.Free();
		
		////////////////////////////////LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!LOOP!////////////////////////////////
		bool is_lose = false, is_end_game = false;
		int number_of_map_now = 0;

		while (is_end_game == false){
			++number_of_map_now;
			char link_map[30];
			sprintf_s(link_map, "map/map%d.txt", number_of_map_now);

			GameMap game_map;
			game_map.loadMap(link_map);
			game_map.loadTiles(g_screen);
			game_map.loadTilesLine(g_screen);
			game_map.loadEffectHint(g_screen, "EffectPokemonHint/");
		
			int time_start = SDL_GetTicks();
			int time_last_click = time_start;
			bool isFindHint = false;
			DoubleNode two_node;

			while (is_play == true){
				bool is_mouse = false, isClick = false;
				while (SDL_PollEvent(&g_event) != 0){
					if (g_event.type == SDL_QUIT){
						close();
						return 0;
					}
					else 
						is_mouse = true;
				}

				//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);//Set mau
				SDL_RenderClear(g_screen);// Clear man hinh

				g_background.Render(g_screen, NULL); // Ve background len g_screen

				///////////////////////////////////////////////////////
				int time_val = SDL_GetTicks()/1000 - time_start/1000;
				time_val = TIMEMAX - time_val;
				int minute = time_val / 60, second = time_val % 60;
				std::string s_minute = std::to_string(minute), s_second = std::to_string(second);
				if (s_minute.size() == 1) s_minute = "0" + s_minute;
				if (s_second.size() == 1) s_second = "0" + s_second;

				std::string str_val = s_minute + ":" + s_second;
				TEXT = str_val;

				dem_nguoc.setText(TEXT);
				dem_nguoc.setColor(0);
				dem_nguoc.createGameText(font, g_screen);
				dem_nguoc.drawText(g_screen, NULL);
				dem_nguoc.Free();

				TEXT = "LEVEL " + std::to_string(number_of_map_now);
				level_text.setText(TEXT);
				level_text.setColor(0);
				level_text.createGameText(font, g_screen);
				level_text.drawText(g_screen, NULL);
				level_text.Free();
				////////////////////////////////////////////////////////
				game_map.drawMap(g_screen);

				if (is_mouse == true){
					isClick = game_map.changeButtonStatus(g_event, g_screen, click_sound);
					if (isClick == true){
						time_last_click = SDL_GetTicks();
						isFindHint = false;
					}
				}

				int time_wait = SDL_GetTicks() - time_last_click;
				if (time_wait/1000 > TIME_WAIT_HINT){
					if (isFindHint == false){
						isFindHint = true;
						two_node = game_map.findRoadHint(g_screen);
					}
					time_wait = time_wait / 50 % 5;
					game_map.effect_pokemon_hint_.showEffect(g_screen, time_wait, makeNode(two_node.node1_.x * TILE_SIZE, two_node.node1_.y * TILE_SIZE));
					game_map.effect_pokemon_hint_.showEffect(g_screen, time_wait, makeNode(two_node.node2_.x * TILE_SIZE, two_node.node2_.y * TILE_SIZE));
				}
				////////////////////////////////////////////////////////
				SDL_RenderPresent(g_screen);
				
				if (time_val == 0) {
					is_play = false;
					is_lose = true;
					is_end_game = true;
				}
				if (game_map.num_of_button_has_not_been_deleted_ == 0){
					is_play = false;
					DoWhenYouClearAMap();
				}
			}

			if (number_of_map_now == NUM_OF_MAP) 
				is_end_game = true;
			is_play = true;
		}

		//////////////////////////////////////////////SHOW_WHEN_YOU_LOST_THE_GAME////////////////////////////////////////////////////
		
		if (is_lose)
			Mix_PlayMusic(loser_sound, 0);
		else
			Mix_PlayChannel(-1, victory_sound, 0);
		ButtonReal menu_button(MENU_RECT_X, MENU_RECT_Y, MENU_SIZE_H, MENU_SIZE_W, g_screen, "sprite/Menu");
		ButtonReal quit_button(QUIT_RECT_X, QUIT_RECT_Y, QUIT_SIZE_H, QUIT_SIZE_W, g_screen, "sprite/Quit");

		bool is_play_again = false;
		while (is_play_again == false){
			bool is_mouse = false;
			while (SDL_PollEvent(&g_event) != 0){
				if (g_event.type == SDL_QUIT){
					close();
					return 0;
				}
				else 
					is_mouse = true;
			}

			//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);//Set mau
			SDL_RenderClear(g_screen);// Clear man hinh
			if (is_lose)
				g_lose.Render(g_screen, NULL);
			else 
				g_win_end_game.Render(g_screen, NULL);

			if (is_mouse == true){
				is_quit = quit_button.handle_events(g_event, click_sound);	
				is_play_again = menu_button.handle_events(g_event, click_sound);
			}
			menu_button.SHOW(g_screen);
			quit_button.SHOW(g_screen);
		
			SDL_RenderPresent(g_screen);
			if (is_quit == true){
				SDL_Delay(200);
				break;
			}
		}
		menu_button.Free();
		quit_button.Free();
		///////////////////////////////////////////THEEEEEEEEEEEEEEEEEEEEEEEEENDDDDDDDDDDDDDDDDDD/////////////////////////////////////////
	}
	close();
	
	return 0;
}