#include "stdafx.h"
#include "TileMap.h"

bool GameMap::checkIfNodeInsideTheMap(NODE_ temp){
	return (temp.x >= 0 && temp.x < MAX_MAP_X && temp.y >= 0 && temp.y < MAX_MAP_Y && game_map_.tile[temp.y][temp.x] == 0);
}

void GameMap::eraseNode(NODE_ A, NODE_ B){
	game_map_.tile[A.y][A.x] = 0;
	game_map_.tile[B.y][B.x] = 0;
}

GameMap::GameMap(){
	for (int i = 0; i < MAX_MAP_Y; i++)
		for (int j = 0; j < MAX_MAP_X; j++)
			my_button_[i][j].setInfomation(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	num_of_button_clicked_ = 0;
	num_of_button_has_not_been_deleted_ = BOARD_HEIGHT * BOARD_WIDTH;

	//Way 0 va 3 doi xung, Way 1 va 2 doi xung
	Way_[0].x = 0; Way_[0].y = 1;
	Way_[1].x = 1; Way_[1].y = 0;
	Way_[2].x = -1; Way_[2].y = 0;
	Way_[3].x = 0; Way_[3].y = -1;
}

void GameMap::loadMap(char* name){// Load file thong tin map
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
		return;

	for (int i = 0; i < MAX_MAP_Y; i++){
		for (int j = 0; j < MAX_MAP_X; j++){
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
		}
	}

	game_map_.file_name_ = name;
	fclose(fp);
}

void GameMap::loadTiles(SDL_Renderer* screen){
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILES; i++){
		sprintf_s(file_img, "map/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
			continue;

		fclose(fp);
		tile_mat_[i][1].loadImage(file_img, screen);
	}

	for (int i = 0; i < MAX_TILES; i++){
		sprintf_s(file_img, "map/%dshift2.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
			continue;

		fclose(fp);
		tile_mat_[i][2].loadImage(file_img, screen);
	}

	for (int i = 0; i < MAX_TILES; i++){
		sprintf_s(file_img, "map/%dshift1.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
			continue;

		fclose(fp);
		tile_mat_[i][3].loadImage(file_img, screen);
	}

}

void GameMap::loadTilesLine(SDL_Renderer* screen){
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < 7; i++){
		sprintf_s(file_img, "Lineeee/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
			continue;

		fclose(fp);
		tile_line_[i].loadImage(file_img, screen);
	}
}

void GameMap::loadEffectHint(SDL_Renderer* screen, std::string path){
	effect_pokemon_hint_.loadEffect(screen, path,NUM_OF_POKEMON_HINT_EFFECT_SPRITE);
}

bool GameMap::changeButtonStatus(SDL_Event m_event, SDL_Renderer* screen, Mix_Chunk* click_sound){
	bool is_clicked = false;

	for (int i = 0; i < MAX_MAP_Y; i++)
		for (int j = 0; j < MAX_MAP_X; j++)
		if (game_map_.tile[i][j] > 0){
			bool ok = my_button_[i][j].handle_events(m_event);
			//Click!!!
			if (ok == true){
				is_clicked = true;
				Mix_PlayChannel(-1, click_sound, 0);
				clicked_[num_of_button_clicked_++] = makeNode(j, i);
			}
			//2 button clicked !!!!!!
			if (num_of_button_clicked_ == 2){
				num_of_button_clicked_ = 0;
				if (game_map_.tile[clicked_[0].y][clicked_[0].x] == game_map_.tile[clicked_[1].y][clicked_[1].x] && 
					checkTheLine(screen, clicked_[0], clicked_[1], false)){
					num_of_button_has_not_been_deleted_ -= 2;
				}
				else {
					my_button_[clicked_[0].y][clicked_[0].x].status_ = 1;
					my_button_[clicked_[1].y][clicked_[1].x].status_ = 1;
				}
			}	
		}
	return is_clicked;
}

void GameMap::drawMap(SDL_Renderer* screen){
	for (int i = 0; i < MAX_MAP_Y; i++){
		for (int j = 0; j < MAX_MAP_X; j++){
			int val = game_map_.tile[i][j];
			if (val > 0){
				tile_mat_[val][my_button_[i][j].status_].setRect(j * TILE_SIZE, i * TILE_SIZE);// Dat sprite len vi tri j * TILE_SIZE, i * TILE_SIZE
				tile_mat_[val][my_button_[i][j].status_].Render(screen);// Render sprite len screen
			}
		}
	}
}

bool GameMap::checkTheLine(SDL_Renderer* screen, NODE_ nodeFirst, NODE_ nodeLast, bool isFindHintLine){
	vector<NodeLine> listNode;
	listNode.clear();
	queue<NodeLine> myQueue;
	NodeLine tempNode;
	tempNode.direct_ = -1;
	tempNode.Toado = nodeFirst;
	tempNode.MS_ = 0;
	tempNode.MS_truoc_ = -1;
	myQueue.push(tempNode);
	listNode.push_back(tempNode);
	/////////////Chay 3 turn de check duong di///////////////////
	for (int TURN = 0; TURN < 3; TURN++){
		queue<NodeLine> tempQueue;
		while (myQueue.size()){

			NodeLine nodeU = myQueue.front();
			myQueue.pop();
			for (int i = 0; i < 4; i++)
			if (nodeU.direct_ == -1 ||
				(nodeU.direct_ != i && nodeU.direct_ + i != 3)){
				for (int j = 1; j <= 100; j++){
					NodeLine nodeV;
					nodeV.direct_ = i;
					nodeV.Toado.x = nodeU.Toado.x + Way_[i].x * j;
					nodeV.Toado.y = nodeU.Toado.y + Way_[i].y * j;
					nodeV.MS_ = listNode.size();
					nodeV.MS_truoc_ = nodeU.MS_;
					
					if (sosanh(nodeV.Toado, nodeLast) ){//Thoa man
						if (isFindHintLine == false){
							drawLine(listNode, nodeV, screen);
							eraseNode(nodeFirst, nodeLast);
						}
						return 1;
					}
					
					if (checkIfNodeInsideTheMap(nodeV.Toado)){
						tempQueue.push(nodeV);
						listNode.push_back(nodeV);
					}
					else break;
				}
			}
		}
		myQueue = tempQueue;//Gan lai myQueue de chay tiep
	}
	return 0;
}

void GameMap::drawLine(vector<NodeLine> vt, NodeLine temp, SDL_Renderer* screen){
	int MsLine[MAX_MAP_Y][MAX_MAP_X];
	for (int i = 0; i < MAX_MAP_Y; i++)
		for (int j = 0; j < MAX_MAP_X; j++)
			MsLine[i][j] = 0;

	while (temp.MS_ != 0){
		NodeLine trc = vt[temp.MS_truoc_];
		/////////////////Ve duong ngang doc/////////////////////
		if (temp.direct_ == 0 || temp.direct_ == 3){// Down Up
			for (int i = min(trc.Toado.y, temp.Toado.y) + 1; i < max(trc.Toado.y, temp.Toado.y); i++)
				MsLine[i][temp.Toado.x] = 1;
		}
		else if (temp.direct_ == 1 || temp.direct_ == 2){// Left Right
			for (int i = min(trc.Toado.x, temp.Toado.x) + 1; i < max(trc.Toado.x, temp.Toado.x); i++)
				MsLine[temp.Toado.y][i] = 2;
		}
		////////////////Ve goc vuong////////////////////////////
		if (temp.direct_ == 0){
			if (trc.direct_ == 1) MsLine[trc.Toado.y][trc.Toado.x] = 6;
			else if (trc.direct_ == 2) MsLine[trc.Toado.y][trc.Toado.x] = 5;
		}
		if (temp.direct_ == 3){
			if (trc.direct_ == 1) MsLine[trc.Toado.y][trc.Toado.x] = 3;
			else if (trc.direct_ == 2) MsLine[trc.Toado.y][trc.Toado.x] = 4;
		}
		if (temp.direct_ == 1){
			if (trc.direct_ == 0) MsLine[trc.Toado.y][trc.Toado.x] = 4;
			else if (trc.direct_ == 3) MsLine[trc.Toado.y][trc.Toado.x] = 5;
		}
		if (temp.direct_ == 2){
			if (trc.direct_ == 0) MsLine[trc.Toado.y][trc.Toado.x] = 3;
			else if (trc.direct_ == 3) MsLine[trc.Toado.y][trc.Toado.x] = 6;
		}

		temp = trc;
	}

	///////////////////////////////////////DRAW!!!!!!!!!!!!/////////////////////////////

	for (int i = 0; i < MAX_MAP_Y; i++){
		for (int j = 0; j < MAX_MAP_X; j++){
			int val = MsLine[i][j];
			if (val > 0){
				tile_line_[val].setRect(j * TILE_SIZE, i * TILE_SIZE);// Dat sprite len vi tri j * TILE_SIZE, i * TILE_SIZE
				tile_line_[val].Render(screen);// Render sprite len screen
			}
		}
	}
	SDL_RenderPresent(screen);
	SDL_Delay(100);

	return;
}

DoubleNode GameMap::findRoadHint(SDL_Renderer* screen){
	DoubleNode res;
	for (int i = 0; i < MAX_MAP_Y; i++)
	for (int j = 0; j < MAX_MAP_X; j++)
	if (game_map_.tile[i][j] > 0){
		for (int i2 = i; i2 < MAX_MAP_Y; i2++)
		for (int j2 = 0; j2 < MAX_MAP_X; j2++)
		if (game_map_.tile[i2][j2] > 0 && 
			(i != i2 || j != j2) &&
			game_map_.tile[i][j] == game_map_.tile[i2][j2]){
			NODE_ firstNode = makeNode(j, i);
			NODE_ secondNode = makeNode(j2, i2);
			if (checkTheLine(screen, firstNode, secondNode, true)){
				res.node1_ = firstNode;
				res.node2_ = secondNode;
				return res;
			}
		}
	}
	return res;
}