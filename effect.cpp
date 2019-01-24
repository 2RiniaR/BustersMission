#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "effect.h"

using namespace std;

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：コンストラクタ
//---------------------------------------------------------------------------
EFFECT_OBJMGR::EFFECT_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	common->effect = this;
	effect = new std::list<EFFECT_OBJECT*>;
	reset = new std::list<int>;
	GrHandle = new std::vector<int>;

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：初期処理
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Initialize() {

	InitGr();

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->Initialize();

		}
	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：終了処理
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Finalize() {

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：更新処理
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Update() {

	int i = 0;

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->Update();
			i++;
		}
	}

	//削除リストresetに入っているキャラデータを一括削除
	ResetListElement();

}


//---------------------------------------------------------------------------
//EFFECT_OBJMGR：描画処理
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Draw() {

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：敵を追加する
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::AddEffect(EFFECT_OBJECT *effectdata) {

	effect->push_back(effectdata);
	effectdata->InputItr(effect->size());
	effectdata->InputMgr(this);

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR：敵を削除する
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::RemoveEffect(int itrnum) {

	reset->push_back(itrnum);	//削除リストresetに登録

}

void EFFECT_OBJMGR::InitGr() {

	GrHandle->push_back(LoadGraph("data/image/effect/effect1.png"));		// 0
	GrHandle->push_back(LoadGraph("data/image/effect/effect2.png"));		// 1
	GrHandle->push_back(LoadGraph("data/image/effect/effect3.png"));		// 2

}


void EFFECT_OBJMGR::ResetListElement() {

	//削除リストresetに入っているキャラデータを一括削除
	if (reset->empty() == false) {
		reset->sort();
		auto itr_reset = reset->begin();
		int i = 0;

		for (auto itr = effect->begin(); itr != effect->end();) {

			if (*itr_reset == i) {

				if ((*itr) != NULL) {
					delete (*itr);
					//(*itr) = NULL;
				}

				itr = effect->erase(itr);
				itr_reset++;
				if (itr_reset == reset->end()) break;

			}
			else {
				++itr;
			}
			i++;

		}
		reset->clear();
	}

}



//---------------------------------------------------------------------------
//EFFECT_OBJECT：イニシャライザ
//---------------------------------------------------------------------------
EFFECT_OBJECT::EFFECT_OBJECT(EffectType type, int ofset, COMMON_DATA *common, POINT2D *pos) {

	this->common = common;
	this->timer = ofset;
	this->type = type;
	this->pos = *pos;
	this->mgrp = common->effect;

	switch (type) {

	case GreenEffect:
		this->GrHandle = mgrp->GetGrHandle(0);
		break;

	case RedEffect:
		this->GrHandle = mgrp->GetGrHandle(1);
		break;

	case ExplosionEffect:
		this->GrHandle = mgrp->GetGrHandle(2);
		break;

	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJECT：デストラクタ
//---------------------------------------------------------------------------
EFFECT_OBJECT::~EFFECT_OBJECT() {

	

}

//---------------------------------------------------------------------------
//EFFECT_OBJECT：初期処理
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//EFFECT_OBJECT：終了処理
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//EFFECT_OBJECT：更新処理
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Update() {

	timer++;

	switch (type) {

	case GreenEffect:
		if (timer > 24) RemoveForList();
		break;

	case RedEffect:
		if (timer > 24) RemoveForList();
		break;

	case ExplosionEffect:
		if (timer > 24) RemoveForList();
		break;

	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJECT：描画処理
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Draw() {

	switch (type) {

	case GreenEffect:
		DrawRectGraph(pos.x - 8 - common->camera->GetCameraPos().x, pos.y - 8 - common->camera->GetCameraPos().y, 16*(timer/8), 0, 16, 16, GrHandle, true, false);
		break;

	case RedEffect:
		DrawRectGraph(pos.x - 8 - common->camera->GetCameraPos().x, pos.y - 8 - common->camera->GetCameraPos().y, 16 * (timer / 8), 0, 16, 16, GrHandle, true, false);
		break;

	case ExplosionEffect:
		DrawRectGraph(pos.x - 8 - common->camera->GetCameraPos().x, pos.y - 8 - common->camera->GetCameraPos().y, 16 * (timer / 8), 0, 16, 16, GrHandle, true, false);
		break;

	}

}

void EFFECT_OBJECT::InputItr(int itrnum) {
	this->itrnum = itrnum;
}

void EFFECT_OBJECT::InputMgr(EFFECT_OBJMGR *mgrpointer) {
	this->mgrp = mgrpointer;
}

void EFFECT_OBJECT::RemoveForList() {
	mgrp->RemoveEffect(itrnum);
}
