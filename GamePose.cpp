#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "key.h"
#include "GamePose.h"

GAME_POSE::GAME_POSE(GAME *gamemgr, COMMON_DATA *common) : BASE_GAMESC(gamemgr){

	this->common = common;
	//Pose = 0;

}

void GAME_POSE::Initialize() {

	GrHandle = LoadGraph("data/image/other/pause.png");

}

void GAME_POSE::Finalize() {



}

void GAME_POSE::Update() {

	if (common->key->GetKeyStatus(KEY_INPUT_M) == 1) {
	
		ChangeGameScene(NowGame_scene);

	}

	if(common->key->GetKeyStatus(KEY_INPUT_Z) == 1){
	
		game->GameStageSet(1);
		ChangeCommonScene(eScene_Start);
	
	}

}

void GAME_POSE::Draw() {

	DrawRectGraph(200, 150, 0, 0, 400, 300, GrHandle, false);

}
