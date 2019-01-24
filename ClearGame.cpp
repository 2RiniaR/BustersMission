#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "key.h"
#include "ClearGame.h"

GAME_CLEAR::GAME_CLEAR(GAME *gamemgr, COMMON_DATA *common) : BASE_GAMESC(gamemgr) {

	this->common = common;
	font = CreateFontToHandle("TypeOne Regular", 60, 7, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font2 = CreateFontToHandle("TypeOne Regular", 26, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

}

void GAME_CLEAR::Initialize() {

	GrHandle = LoadGraph("data/image/other/centerbar.png");

}

void GAME_CLEAR::Finalize() {



}

void GAME_CLEAR::Update() {

	time++;

	if (common->key->GetKeyStatus(KEY_INPUT_Z) == 1 && time > 240) {

		if (*game->GameStage == 3) {
			ChangeCommonScene(eScene_Result);
			game->GameStageSet(1);
		}
		else {
			game->GameStageSet(*game->GameStage + 1);
			*game->LeftLife += (100 - *game->LeftLife) / 2;
			if (*game->LeftLife > 100) *game->LeftLife = 100;
			ChangeCommonScene(eScene_Game);
		}

	}

}

void GAME_CLEAR::Draw() {

	if (60 <= time && time < 140) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawRectGraph(0, 0, 0, 0, 10 * (time - 60), 600, GrHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if(140 <= time){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawRectGraph(0, 0, 0, 0, 800, 600, GrHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if(time > 160) DrawFormatStringFToHandle(160, 240, GetColor(0, 255, 255), font, "MISSION\n      CLEARED!!");

	if(time > 220  && *this->game->GameStage <= 2)  DrawFormatStringFToHandle(280, 510, GetColor(255, 255, 105), font2, "HP +");

}
