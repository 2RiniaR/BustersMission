#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "key.h"
#include "GameSystem.h"

GAME_SYSTEM::GAME_SYSTEM(GAME *gamemgr, COMMON_DATA *common, int stage) : BASE_GAMESC(gamemgr){

	this->common = common;
	Score = 0;
	GameTimer = 0;
	LeaveEnemy = 0;
	Stage = stage;

	Pose = 0;

}

void GAME_SYSTEM::Initialize() {



}

void GAME_SYSTEM::Finalize() {



}

void GAME_SYSTEM::Update() {

	isPlayerLeave = common->player->data->islive;
	LeaveEnemy = common->chara->CountEnemy;

	if (common->key->GetKeyStatus(KEY_INPUT_M) == 1 && game->GetGameScene() == NowGame_scene) {

		this->ChangeGameScene(Pose_scene);

	}

	if (LeaveEnemy == 0) {

		this->ChangeGameScene(ClearGame_scene);

	}

	if (isPlayerLeave == false) {

		this->ChangeGameScene(GameOver_scene);

	}

}

void GAME_SYSTEM::Draw() {



}
