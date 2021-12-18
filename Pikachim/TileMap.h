#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Common.h"
#include "BaseObject.h"
#include "MakeButton.h"
#include "Effect.h"
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_TILES 40

class TileMat : public BaseObject{
public:
	TileMat() {;}
	~TileMat() {;}
};

class GameMap{// Quan li xay dung map
public:
	GameMap();
	~GameMap() {;}

	void loadMap(char* name);
	void loadTiles(SDL_Renderer* screen);
	void loadTilesLine(SDL_Renderer* screen);
	void loadEffectHint(SDL_Renderer* screen, std::string path);

	bool changeButtonStatus(SDL_Event m_event, SDL_Renderer* screen,  Mix_Chunk* click_sound);
	bool checkTheLine(SDL_Renderer* screen, NODE_ node_first, NODE_ node_last, bool is_find_hint_line);
	bool checkIfNodeInsideTheMap(NODE_ temp);
	void eraseNode(NODE_ A, NODE_ B);
	DoubleNode findRoadHint(SDL_Renderer* screen);
	
	void drawMap(SDL_Renderer* screen);
	void drawLine(vector<NodeLine> vt, NodeLine temp, SDL_Renderer* screen);
//private:

	int num_of_button_clicked_;
	int num_of_button_has_not_been_deleted_;
	NODE_ clicked_[2], Way_[4];
	MAP game_map_;
	TileMat tile_mat_[MAX_TILES][4];
	BaseObject tile_line_[10];
	Effect effect_pokemon_hint_;

	Button my_button_[MAX_MAP_Y][MAX_MAP_X];
};

#endif