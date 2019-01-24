#pragma once

class GAME_CONFIG;
class KEY_INFO;

#define EXT 1

//----------------------------------------------------------
// シーンの列挙体
//----------------------------------------------------------
enum eScene{

	eScene_Start,   //スタート
	eScene_Config,  //設定
	eScene_Game,    //ゲーム
	eScene_Result,

	eScene_None    //無し

};

enum eFade {

	eFade_in,
	eFade_stay,
	eFade_out

};

//----------------------------------------------------------
// TASK クラス
//----------------------------------------------------------
class TASK {

public:
	GAME_CONFIG *game_config;		//ゲーム設定情報
	KEY_INFO *key;					//キー情報の格納
	int *GameStage;
	int *PlayerScore;
	int *LeftTime;
	int *LeftLife;

	virtual ~TASK() {}
	virtual void Initialize() {}    //初期化処理
	virtual void Finalize() {}		//終了処理
	virtual void Update() = 0;		//更新処理
	virtual void Draw() = 0;		//描画処理

	void GameStageSet(int stage) { *GameStage = stage; };

};

//----------------------------------------------------------
// SCENE_CHANGER クラス
//----------------------------------------------------------
class SCENE_CHANGER {

public:
	virtual void ChangeScene(eScene NextScene) = 0;			//指定シーンに変更する
	virtual void ChangeSceneWithFade(eScene NextScene) = 0;	//フェード処理ありで指定シーンに変更する
	virtual void SceneUpdate() = 0;

};

//----------------------------------------------------------
// FADE_MGR クラス
//----------------------------------------------------------
class FADE_MGR {

public:
	FADE_MGR() { mFade = eFade_stay, bright = 255; };
	eScene fNextScene;

protected:
	int bright;
	eFade mFade;
	virtual void FadeIn() = 0;
	virtual void FadeOut() = 0;
	void Change_Fade(eFade NextFade) { mFade = NextFade; };

};

//----------------------------------------------------------
// BASE_SCENE クラス
//----------------------------------------------------------
class BASE_SCENE :public TASK{

protected:
	SCENE_CHANGER *mSceneChanger;	//クラス所有元にシーン切り替えを伝えるインターフェイス

public:
	BASE_SCENE(SCENE_CHANGER* changer) { mSceneChanger = changer; };
	virtual ~BASE_SCENE() {}
	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update() {};
	virtual void Draw() {};

};

//----------------------------------------------------------
// SCENE_MGR クラス
//----------------------------------------------------------
class SCENE_MGR : public SCENE_CHANGER, TASK, FADE_MGR{

private:
	BASE_SCENE *mScene;		//シーン管理変数
	eScene mNextScene;		//次のシーン管理変数

	
	void SceneUpdate();
	void FadeIn();
	void FadeOut();

public:
	SCENE_MGR();
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

	void ChangeScene(eScene NextScene);  // 引数 nextScene にシーンを変更する
	void ChangeSceneWithFade(eScene NextScene);  // フェード処理で引数 nextScene にシーンを変更する

};

double pi();
double to_deg(double r);
double to_rad(double d);
void rad_zero(double *r);