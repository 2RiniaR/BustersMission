#pragma once

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

#include "sceneMGR.h"

#define EPS 0.000001f // Œë·
#define WINDOW_X 800
#define WINDOW_Y 600
#define GAMESCREEN_X 800
#define GAMESCREEN_Y 500

class PLAYER_OBJMGR;
class MAP_OBJMGR;
class CHARA_OBJMGR;
class ITEM_OBJMGR;
class SOUND_OBJMGR;
class EFFECT_OBJMGR;
class COMMON_DATA;
class CAMERA_OBJMGR;
class KEY_INFO;
class SCENE_CHANGER;
class HIT_OBJMGR;
class USERITF_OBJMGR;
class GAME_SYSTEM;

class GAME_START;
class GAME_OVER;
class GAME_CLEAR;
class GAME_POSE;

enum GameScene {

	StartGame_scene,
	NowGame_scene,
	GameOver_scene,
	ClearGame_scene,
	Pose_scene

};


class GAME : public BASE_SCENE {

private:
	GameScene Scene;

	GAME_SYSTEM *GameSystem;
	MAP_OBJMGR *Map;
	CHARA_OBJMGR *Chara;
	ITEM_OBJMGR *Item;
	SOUND_OBJMGR *Sound;
	EFFECT_OBJMGR *Effect;
	COMMON_DATA *common;
	HIT_OBJMGR *hit;
	CAMERA_OBJMGR *Camera;
	USERITF_OBJMGR *Useritf;

	GAME_START *GameStart;
	GAME_CLEAR *GameClear;
	GAME_POSE *GamePose;
	GAME_OVER *GameOver;

	int GameStartBGM;
	int StageBGM;
	int GameOverBGM;
	int GameClearBGM;

public:
	GAME(int *time, int *life, int *score, int *stage, SCENE_CHANGER* changer);
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	GameScene GetGameScene() { return Scene; }

	void ChangeGameScene(GameScene s) { Scene = s; };
	void ChangeCommonScene(eScene nextScene) { this->mSceneChanger->ChangeSceneWithFade(nextScene); }
	void ForceBGMStop();

};
