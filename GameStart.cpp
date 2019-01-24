#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "key.h"
#include "GameStart.h"

GAME_START::GAME_START(GAME *gamemgr, COMMON_DATA *common) : BASE_GAMESC(gamemgr) {

	this->common = common;
	font = CreateFontToHandle("TypeOne Regular", 60, 7, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

}

void GAME_START::Initialize() {

	GrHandle = LoadGraph("data/image/other/centerbar.png");

}

void GAME_START::Finalize() {



}

void GAME_START::Update() {

	time++;

	if (time > 200) {

		ChangeGameScene(NowGame_scene);

	}

}

void GAME_START::Draw() {

	if (0 <= time && time < 80) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawRectGraph(0, 0, 0, 0, 10 * time, 600, GrHandle, true);
	}
	else if (80 <= time) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawRectGraph(0, 0, 0, 0, 800, 600, GrHandle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if(time > 60)
		DrawFormatStringFToHandle(250, 220, GetColor(255, 100, 0), font, "STAGE %d", *game->GameStage);

	if(time > 140)
		DrawFormatStringFToHandle(80, 320, GetColor(0, 35, 255), font, "MISSION  START!!");

}
