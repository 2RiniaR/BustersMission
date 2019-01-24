#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "DxLib.h"
#include "sceneMGR.h"
#include "gclass.h"
#include "gconf.h"
#include "key.h"
#include "hit.h"
#include "chara.h"
#include "effect.h"
#include "item.h"
#include "map.h"
#include "player.h"
#include "sound.h"
#include "camera.h"
#include "useritf.h"
#include "GameSystem.h"
#include "GameOver.h"
#include "GamePose.h"
#include "GameStart.h"
#include "ClearGame.h"
#include "game.h"

//■■■■■■■■■■■■コンストラクタ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
GAME::GAME(int *time, int *life, int *score, int *stage, SCENE_CHANGER* changer) : BASE_SCENE(changer) {

	Scene = StartGame_scene;

	if (*stage == 1) { *time = 0, *score = 0, *life = 100; };

}

//■■■■■■■■■■■■初期化■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void GAME::Initialize() {

	common = new COMMON_DATA;
	common->key = key;
	GameSystem = new GAME_SYSTEM(this, common, *GameStage);
	hit = new HIT_OBJMGR(common);
	Item = new ITEM_OBJMGR(common);
	Effect = new EFFECT_OBJMGR(common);
	Chara = new CHARA_OBJMGR(common, *GameStage, *LeftLife);
	Map = new MAP_OBJMGR(common, *GameStage);
	Sound = new SOUND_OBJMGR(common);
	Camera = new CAMERA_OBJMGR(common);
	Useritf = new USERITF_OBJMGR(common, *GameStage, *LeftTime);
	GameStart = new GAME_START(this, common);
	GameOver = new GAME_OVER(this, common);
	GameClear = new GAME_CLEAR(this, common);
	GamePose = new GAME_POSE(this, common);
	
	GameSystem->Initialize();
	GameStart->Initialize();
	GameOver->Initialize();
	GameClear->Initialize();
	GamePose->Initialize();
	Effect->Initialize();
	Chara->Initialize();
	Map->Initialize();
	Camera->Initialize();
	Useritf->Initialize();

	GameStartBGM = LoadSoundMem("data/sound/se/storm_land.mp3");
	
	switch (*GameStage) {

	case 1:
		StageBGM = LoadSoundMem("data/sound/bgm/Dungeon-Cave_loop.ogg");

	case 2:
		StageBGM = LoadSoundMem("data/sound/bgm/Es-STAGE1_loop.ogg");

	case 3:
		StageBGM = LoadSoundMem("data/sound/bgm/RRR_loop.ogg");

	};


	GameOverBGM = LoadSoundMem("data/sound/se/se_maoudamashii_onepoint29.wav");
	GameClearBGM = LoadSoundMem("data/sound/se/se_maoudamashii_jingle05.wav");

}

//■■■■■■■■■■■■終了処理■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void GAME::Finalize() {

	Chara->Finalize();
	Effect->Finalize();
	Map->Finalize();
	Useritf->Finalize();
	GameSystem->Finalize();
	ForceBGMStop();
	
}

//■■■■■■■■■■■■更新■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void GAME::Update() {

	*this->LeftLife = common->player->data->health;

	switch (Scene) {

	case StartGame_scene:
		PlaySoundMem(GameStartBGM, DX_PLAYTYPE_BACK);
		GameStart->Update();
		break;

	case NowGame_scene:
		if (CheckSoundMem(GameStartBGM) == 1) {
			ForceBGMStop();
		}

		if (CheckSoundMem(StageBGM) == 0) {
			PlaySoundMem(StageBGM, DX_PLAYTYPE_LOOP);
		}

		*this->LeftTime = *(this->LeftTime) + 1;
		Map->Update();
		Chara->Update();
		Effect->Update();
		hit->Update();
		Camera->Update();
		Useritf->Update();
		GameSystem->Update();
		break;

	case GameOver_scene:

		if (CheckSoundMem(StageBGM) == 1) {
			ForceBGMStop();
		}

		if (CheckSoundMem(GameOverBGM) == 0) {
			PlaySoundMem(GameOverBGM, DX_PLAYTYPE_BACK);
		}

		GameOver->Update();
		break;

	case ClearGame_scene:

		if (CheckSoundMem(StageBGM) == 1) {
			ForceBGMStop();
		}

		if (CheckSoundMem(GameClearBGM) == 0) {
			PlaySoundMem(GameClearBGM, DX_PLAYTYPE_BACK);
		}

		GameClear->Update();
		break;

	case Pose_scene:
		GamePose->Update();
		break;

	}

}

//■■■■■■■■■■■■描画■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void GAME::Draw() {

	//背景初期化
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), 1);

	Map->Draw();
	Chara->Draw();
	Effect->Draw();
	Useritf->Draw();
	GameSystem->Draw();

	switch(Scene) {

	case StartGame_scene:
		GameStart->Draw();
		break;

	case NowGame_scene:
		break;

	case GameOver_scene:
		GameOver->Draw();
		break;

	case ClearGame_scene:
		GameClear->Draw();
		break;

	case Pose_scene:
		GamePose->Draw();
		break;

	}

}

void GAME::ForceBGMStop() {

	StopSoundMem(GameClearBGM);
	StopSoundMem(GameStartBGM);
	StopSoundMem(StageBGM);
	StopSoundMem(GameOverBGM);

}