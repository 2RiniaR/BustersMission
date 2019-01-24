#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "key.h"
#include "GameOver.h"

GAME_OVER::GAME_OVER(GAME *gamemgr, COMMON_DATA *common) : BASE_GAMESC(gamemgr) {

	this->common = common;

}

void GAME_OVER::Initialize() {

	GrHandle = LoadGraph("data/image/other/gameover.png");

}

void GAME_OVER::Finalize() {



}

void GAME_OVER::Update() {

	time++;

	if (common->key->GetKeyStatus(KEY_INPUT_Z) == 1 && time > 240) {

		game->GameStageSet(1);
		ChangeCommonScene(eScene_Start);

	}

}

void GAME_OVER::Draw() {

	if (60 < time && time < 120) DrawRectGraph(0, 0 - (10*(120-time)), 0, 0, 800, 600, GrHandle, false);
	else if(time >= 120) DrawRectGraph(0, 0, 0, 0, 800, 600, GrHandle, false);

}
