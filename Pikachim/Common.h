#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static Mix_Chunk* click_sound = NULL;
static Mix_Chunk* fail_click_sound = NULL;
static Mix_Chunk* clock_destroyed_sound = NULL;
static Mix_Chunk* win_sound = NULL;
static Mix_Chunk* victory_sound = NULL;

static Mix_Music* music = NULL;
static Mix_Music* loser_sound = NULL;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int SCREEN_WIDTH = 1152;
const int SCREEN_HEIGHT = 624;
const int SCREEN_BPP = 32;

const int CL_KEY_R = 167;
const int CL_KEY_G = 175;
const int CL_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 48
#define PLAY_SIZE_W 144
#define PLAY_SIZE_H 384
#define QUIT_SIZE_W 144
#define QUIT_SIZE_H 384
#define MENU_SIZE_W 144
#define MENU_SIZE_H 384
#define FONTSIZE 17

#define MAX_MAP_X 24
#define MAX_MAP_Y 13
#define TIME_RECT_X 85
#define TIME_RECT_Y 250
#define PLAY_RECT_X 380
#define PLAY_RECT_Y 380
#define MENU_RECT_X 760
#define MENU_RECT_Y 350
#define QUIT_RECT_X 760
#define QUIT_RECT_Y 480
#define CLOCK_EFFECT_RECT_X 25
#define CLOCK_EFFECT_RECT_Y 70
#define LEVEL_TEXT_RECT_X 60
#define LEVEL_TEXT_RECT_Y 30

#define BOARD_HEIGHT 1//9
#define BOARD_WIDTH 2//16

#define TIMEMAX 10//1800
#define NUM_OF_MAP 2
#define TIME_WAIT_HINT 1
#define TIME_DELAY_SPRITE_EFFECT 50
#define NUM_OF_CLOCK_EFFECT_SPRITE 5
#define NUM_OF_POKEMON_HINT_EFFECT_SPRITE 4

struct MAP{// 1 kieu du lieu, chua cac thong tin cua map
	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

struct NODE_{
	int x, y;
};
bool sosanh(NODE_ A, NODE_ B);

NODE_ makeNode(int x, int y);

struct NodeLine{
	NODE_ Toado;
	int direct_;
	int MS_, MS_truoc_;
};

class DoubleNode{
public:
	NODE_ node1_, node2_;
	DoubleNode();
	~DoubleNode() {;}
};

#endif