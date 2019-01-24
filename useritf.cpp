#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "useritf.h"

USERITF_OBJMGR::USERITF_OBJMGR(COMMON_DATA *common, int stage, int gametime) {

	this->common = common;
	useritf = new std::vector<USERITF_OBJECT*>;
	useritf->push_back(new USERITF_BAR(common));
	useritf->push_back(new USERITF_STAGE(common, stage));
	useritf->push_back(new USERITF_PLAYERHP(common));
	useritf->push_back(new USERITF_BOSSHP(common));
	useritf->push_back(new USERITF_ENEMY(common));
	useritf->push_back(new USERITF_TIME(common, gametime));
	useritf->push_back(new USERITF_SCORE(common));

}

void USERITF_OBJMGR::Initialize() {

	if (useritf->empty() == false) {
		for (auto itr = useritf->begin(); itr != useritf->end(); ++itr) {
			(*itr)->mgr = this;
			(*itr)->Initialize();
		}
	}

}

void USERITF_OBJMGR::Finalize() {

	if (useritf->empty() == false) {
		for (auto itr = useritf->begin(); itr != useritf->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

void USERITF_OBJMGR::Update() {

	if (useritf->empty() == false) {
		for (auto itr = useritf->begin(); itr != useritf->end(); ++itr) {
			(*itr)->Update();
		}
	}

}

void USERITF_OBJMGR::Draw() {

	if (useritf->empty() == false) {
		for (auto itr = useritf->begin(); itr != useritf->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}






USERITF_BAR::USERITF_BAR(COMMON_DATA *common) {

	this->common = common;

}

void USERITF_BAR::Initialize() {



}

void USERITF_BAR::Finalize() {



}

void USERITF_BAR::Update() {



}

void USERITF_BAR::Draw() {

	DrawBoxAA(0, GAMESCREEN_Y * EXT, WINDOW_X * EXT, WINDOW_Y * EXT, GetColor(40, 40, 40), true);

}






USERITF_STAGE::USERITF_STAGE(COMMON_DATA *common, int stage) {

	this->common = common;
	this->stagename = stage;

}

void USERITF_STAGE::Initialize() {

	font = CreateFontToHandle("TypeOne Regular", 26 * EXT, 4, DX_FONTTYPE_ANTIALIASING);

}

void USERITF_STAGE::Finalize() {



}

void USERITF_STAGE::Update() {



}

void USERITF_STAGE::Draw() {

	DrawFormatStringToHandle(20 * EXT, 510 * EXT, GetColor(255, 255, 255), font, "STAGE %d", stagename);

}





USERITF_ENEMY::USERITF_ENEMY(COMMON_DATA *common) {

	this->common = common;

}

void USERITF_ENEMY::Initialize() {

	//stagename = 1;
	//font = CreateFontToHandle(NULL, 64, 5, DX_FONTTYPE_ANTIALIASING);

}

void USERITF_ENEMY::Finalize() {



}

void USERITF_ENEMY::Update() {



}

void USERITF_ENEMY::Draw() {

	//DrawFormatStringToHandle(20, 460, GetColor(255, 255, 255), font, "ENEMY %d", stagename);

}




USERITF_SCORE::USERITF_SCORE(COMMON_DATA *common) {

	this->common = common;

}

void USERITF_SCORE::Initialize() {

	score = 0;
	font = CreateFontToHandle(NULL, 64 * EXT, 5, DX_FONTTYPE_ANTIALIASING);

}

void USERITF_SCORE::Finalize() {



}

void USERITF_SCORE::Update() {



}

void USERITF_SCORE::Draw() {

	//DrawFormatStringToHandle(20, 460, GetColor(255, 255, 255), font, "SCORE %d", stagename);

}




USERITF_TIME::USERITF_TIME(COMMON_DATA *common, int gtime) {

	this->common = common;
	timer = gtime;

}

void USERITF_TIME::Initialize() {

	font = CreateFontToHandle("TypeOne Regular", 48 * EXT, 5, DX_FONTTYPE_ANTIALIASING);

}

void USERITF_TIME::Finalize() {



}

void USERITF_TIME::Update() {

	timer++;

}

void USERITF_TIME::Draw() {

	DrawFormatStringToHandle(490 * EXT, 550 * EXT, GetColor(255, 255, 255), font, "TIME %3d", (int)timer/60);

}



USERITF_PLAYERHP::USERITF_PLAYERHP(COMMON_DATA *common) {

	this->common = common;

}

void USERITF_PLAYERHP::Initialize() {

	font = CreateFontToHandle("TypeOne Regular", 32 * EXT, 3, DX_FONTTYPE_ANTIALIASING);
	HP = common->player->data->health;

}

void USERITF_PLAYERHP::Finalize() {



}

void USERITF_PLAYERHP::Update() {

	HP = common->player->data->health;

}

void USERITF_PLAYERHP::Draw() {

	DrawBoxAA(20 * EXT, 540 * EXT, 440 * EXT, 590 * EXT, GetColor(220, 220, 220), true);
	DrawBoxAA(120 * EXT, 550 * EXT, 420 * EXT, 580 * EXT, GetColor(0, 0, 0), true);
	DrawBoxAA(120 * EXT, 550 * EXT, (120 + 3 * HP) * EXT, 580 * EXT, GetColor(0, 255, 50), true);
	DrawFormatStringToHandle(30 * EXT, 548 * EXT, GetColor(0, 0, 125), font, "%3d", HP);

}




USERITF_BOSSHP::USERITF_BOSSHP(COMMON_DATA *common) {

	this->common = common;
	hideflag = true;

}

void USERITF_BOSSHP::Initialize() {

	font = CreateFontToHandle(NULL, 24 * EXT, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

}

void USERITF_BOSSHP::Finalize() {



}

void USERITF_BOSSHP::Update() {

	if (common->chara->boss) hideflag = false;
	else hideflag = true;

}

void USERITF_BOSSHP::Draw() {
	int l;

	if (hideflag == true) return;

	DrawBoxAA(80 * EXT, 10 * EXT, 720 * EXT, 30 * EXT, GetColor(0, 0, 0), true);

	DrawBoxAA(100 * EXT, 15 * EXT, 700 * EXT, 25 * EXT, GetColor(100, 100, 100), true);
	if(common->chara->boss)	l = (int)((double)common->chara->boss->data->health / common->chara->boss->data->MaxHP * 600);
	DrawBoxAA(100 * EXT, 15 * EXT, (100+l) * EXT, 25 * EXT, GetColor(255, 0, 255), true);

}
