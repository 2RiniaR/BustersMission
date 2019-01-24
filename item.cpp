#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "item.h"

using namespace std;

//---------------------------------------------------------------------------
//ITEM_OBJMGR：コンストラクタ
//---------------------------------------------------------------------------
ITEM_OBJMGR::ITEM_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	item = new std::list<ITEM_OBJECT*>;
	reset = new std::list<int>;

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR：初期処理
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Initialize() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Initialize();

		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR：終了処理
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Finalize() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR：更新処理
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Update() {

	int i = 0;

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->Update();
			i++;
		}
	}

	//削除リストresetに入っているキャラデータを一括削除
	ResetListElement();

}


//---------------------------------------------------------------------------
//ITEM_OBJMGR：描画処理
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Draw() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR：敵を追加する
//---------------------------------------------------------------------------
void ITEM_OBJMGR::AddItem(ITEM_OBJECT *itemdata) {

	item->push_back(itemdata);
	itemdata->InputItr(item->size());
	itemdata->InputMgr(this);

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR：敵を削除する
//---------------------------------------------------------------------------
void ITEM_OBJMGR::RemoveItem(int itrnum) {

	reset->push_back(itrnum);	//削除リストresetに登録

}


void ITEM_OBJMGR::ResetListElement() {

	//削除リストresetに入っているキャラデータを一括削除
	if (reset->empty() == false) {
		reset->sort();
		auto itr_reset = reset->begin();
		int i = 0;

		for (auto itr = item->begin(); itr != item->end();) {

			if (*itr_reset == i) {

				if ((*itr) != NULL) {
					delete (*itr);
					//(*itr) = NULL;
				}

				itr = item->erase(itr);
				itr_reset++;

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
//ITEM_OBJECT：イニシャライザ
//---------------------------------------------------------------------------
ITEM_OBJECT::ITEM_OBJECT(ItemType type, POINT2D pos, double size, COMMON_DATA *common) {

	this->common = common;
	this->timer = 0;
	this->type = type;
	this->pos = pos;
	this->hit = new CHARA_HIT(&pos, size, Item_hit, false);

}

//---------------------------------------------------------------------------
//ITEM_OBJECT：デストラクタ
//---------------------------------------------------------------------------
ITEM_OBJECT::~ITEM_OBJECT() {



}

//---------------------------------------------------------------------------
//ITEM_OBJECT：初期処理
//---------------------------------------------------------------------------
void ITEM_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//ITEM_OBJECT：終了処理
//---------------------------------------------------------------------------
void ITEM_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//ITEM_OBJECT：更新処理
//---------------------------------------------------------------------------
void ITEM_OBJECT::Update() {

	timer++;

}

void ITEM_OBJECT::Collision() {

	if (hit->HitCheckOnMove(common->player->hit) == false)	return;

	switch (type) {

	case Health5:
		break;

	case Health10:
		break;

	case Score10:
		break;

	case Score20:
		break;

	case SpeedUp1:
		break;

	case StrengthUp1:
		break;

	case DeffenceUp1:
		break;

	}

	RemoveForList();

}

//---------------------------------------------------------------------------
//ITEM_OBJECT：描画処理
//---------------------------------------------------------------------------
void ITEM_OBJECT::Draw() {



}

void ITEM_OBJECT::InputItr(int itrnum) {
	this->itrnum = itrnum;
}

void ITEM_OBJECT::InputMgr(ITEM_OBJMGR *mgrpointer) {
	this->mgrp = mgrpointer;
}

void ITEM_OBJECT::RemoveForList() {
	mgrp->RemoveItem(itrnum);
}
