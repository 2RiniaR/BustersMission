#include "DxLib.h"
#include "sceneMGR.h"
#include "key.h"
#include "gconf.h"
#include "result.h"
#include <cmath>

//■■■■■■■■■■■■コンストラクタ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
RESULT::RESULT(int time, int life, int score, int stage, SCENE_CHANGER* changer) : BASE_SCENE(changer) {

	this->life= life;
	this->stage = stage;
	this->lefttime = time;
	this->score = score;

}

//■■■■■■■■■■■■初期化■■■■■■■■■■■■
void RESULT::Initialize() {

	GrHandle = LoadGraph("data/image/other/result.png");
	font = CreateFontToHandle("TypeOne Regular", 54, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	score = (100000000 / (lefttime + 0.1)) * sqrt(life);
	
}

//■■■■■■■■■■■■終了処理■■■■■■■■■■■
void RESULT::Finalize() {

	InitFontToHandle(); //すべてのフォントデータの削除

}

//■■■■■■■■■■■■更新■■■■■■■■■■■■
void RESULT::Update() {

	time++;
	
	if (key->GetKeyStatus(KEY_INPUT_Z) == 1 && time > 260) {

		mSceneChanger->ChangeSceneWithFade(eScene_Start);

	}

}

//■■■■■■■■■■■■描画■■■■■■■■■■■■
void RESULT::Draw() {

	DrawGraph(0, 0, GrHandle, false);

	if(time > 60)
		DrawFormatStringToHandle(140, 200, GetColor(100, 200, 0), font, "TIME : %.2lf", (double)lefttime/60);
	if(time > 120)
		DrawFormatStringToHandle(140, 280, GetColor(0, 100, 200), font, "LIFE : %3d", life);
	if(time > 200)
		DrawFormatStringToHandle(140, 460, GetColor(200, 0, 100), font, "SCORE : %4d", score);

}
