#include <vector>
#include <string.h>
#include <math.h>
#include "DxLib.h"
#include "sceneMGR.h"
#include "start.h"
#include "config.h"
#include "game.h"
#include "result.h"
#include "key.h"
#include "gconf.h"


//■■■■■■■■■■■■コンストラクタ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
SCENE_MGR::SCENE_MGR() :mNextScene(eScene_None){ //次のシーン管理変数

	mScene = (BASE_SCENE*) new START(this);
	game_config = new GAME_CONFIG;
	key = new KEY_INFO;
	mScene->game_config = this->game_config;	//ゲーム設定情報の代入
	mScene->key = this->key;					//キー情報の代入
	GameStage = new int;
	*GameStage = 1;
	PlayerScore = new int;
	*PlayerScore = 0;
	LeftLife = new int;
	*LeftLife = 0;
	LeftTime = new int;
	*LeftTime = 0;

}

//■■■■■■■■■■■■初期化■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::Initialize() {

	mScene->Initialize();

}

//■■■■■■■■■■■■終了処理■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::Finalize() {

	mScene->Finalize();
	delete game_config;

}

//■■■■■■■■■■■■更新■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::Update() {

	SceneUpdate();	//Sceneの変更がされていた場合、mSceneを変更
	key->UpdateKey();

	switch (mFade) {

	case eFade_in:
		FadeIn();
		break;

	case eFade_out:
		FadeOut();
		break;

	case eFade_stay:
		mScene->Update(); //シーンの更新
		break;

	}
	
}

//■■■■■■■■■■■■描画■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::Draw() {
	
	mScene->Draw(); //シーンの描画

}

//■■■■■■■■■■■■シーンの変更■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::SceneUpdate() {

	if (mNextScene != eScene_None) {    //次のシーンがセットされていたら

		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;

		switch (mNextScene) {       //シーンによって処理を分岐

		case eScene_Start:        //次の画面がメニューなら
			mScene = (BASE_SCENE*) new START(this);   //メニュー画面のインスタンスを生成する
			break;//以下略

		case eScene_Config:
			mScene = (BASE_SCENE*) new CONFIG(this);
			break;

		case eScene_Game:
			mScene = (BASE_SCENE*) new GAME(LeftTime, LeftLife, PlayerScore, GameStage, this);
			break;

		case eScene_Result:
			mScene = (BASE_SCENE*) new RESULT(*LeftTime, *LeftLife, *PlayerScore, *GameStage, this);
			break;

		}

		mNextScene = eScene_None;					//次のシーン情報をクリア
		mScene->game_config = this->game_config;	//ゲーム設定情報の代入
		mScene->key = this->key;					//キー情報の代入
		mScene->GameStage = this->GameStage;
		mScene->LeftLife = this->LeftLife;
		mScene->LeftTime = this->LeftTime;
		mScene->PlayerScore = this->PlayerScore;
		mScene->Initialize();						//シーンを初期化

	}

}

//■■■■■■■■■■■■ChangeScene()■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::ChangeScene(eScene NextScene) {

	mNextScene = NextScene;    //次のシーンをセットする
	

}

void SCENE_MGR::ChangeSceneWithFade(eScene NextScene) {

	Change_Fade(eFade_out);
	fNextScene = NextScene;

}

//■■■■■■■■■■■■フェードイン■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::FadeIn() {

	bright += 10;
	if (bright > 255) { bright = 255, Change_Fade(eFade_stay); }
	SetDrawBright(bright, bright, bright);

}

//■■■■■■■■■■■■フェードアウト■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void SCENE_MGR::FadeOut() {

	bright -= 10;
	if (bright < 0) { bright = 0, Change_Fade(eFade_in), ChangeScene(fNextScene); }
	SetDrawBright(bright, bright, bright);

}

//----------------------------------------------------------------------------------------

double pi(void) {

	return atan(1.0) * 4.0;

}

double to_deg(double r) {

	return r * 180.0 / (atan(1.0) * 4.0);

}

double to_rad(double d) {

	return (atan(1.0) * 4.0) * d / 180.0;

}

void rad_zero(double *r) {

	//角度の範囲を0から2πまでに制限

	if (*r < 0.0) {
		*r = 2 * pi() + *r;
	}
	else if (*r > 2 * pi()) {
		*r = *r - 2 * pi();
	}
	else {
		*r = *r;
	}

}