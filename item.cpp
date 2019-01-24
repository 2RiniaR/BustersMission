#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "item.h"

using namespace std;

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�R���X�g���N�^
//---------------------------------------------------------------------------
ITEM_OBJMGR::ITEM_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	item = new std::list<ITEM_OBJECT*>;
	reset = new std::list<int>;

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F��������
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Initialize() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Initialize();

		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�I������
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Finalize() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�X�V����
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

	//�폜���X�greset�ɓ����Ă���L�����f�[�^���ꊇ�폜
	ResetListElement();

}


//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�`�揈��
//---------------------------------------------------------------------------
void ITEM_OBJMGR::Draw() {

	if (item->empty() == false) {
		for (auto itr = item->begin(); itr != item->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�G��ǉ�����
//---------------------------------------------------------------------------
void ITEM_OBJMGR::AddItem(ITEM_OBJECT *itemdata) {

	item->push_back(itemdata);
	itemdata->InputItr(item->size());
	itemdata->InputMgr(this);

}

//---------------------------------------------------------------------------
//ITEM_OBJMGR�F�G���폜����
//---------------------------------------------------------------------------
void ITEM_OBJMGR::RemoveItem(int itrnum) {

	reset->push_back(itrnum);	//�폜���X�greset�ɓo�^

}


void ITEM_OBJMGR::ResetListElement() {

	//�폜���X�greset�ɓ����Ă���L�����f�[�^���ꊇ�폜
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
//ITEM_OBJECT�F�C�j�V�����C�U
//---------------------------------------------------------------------------
ITEM_OBJECT::ITEM_OBJECT(ItemType type, POINT2D pos, double size, COMMON_DATA *common) {

	this->common = common;
	this->timer = 0;
	this->type = type;
	this->pos = pos;
	this->hit = new CHARA_HIT(&pos, size, Item_hit, false);

}

//---------------------------------------------------------------------------
//ITEM_OBJECT�F�f�X�g���N�^
//---------------------------------------------------------------------------
ITEM_OBJECT::~ITEM_OBJECT() {



}

//---------------------------------------------------------------------------
//ITEM_OBJECT�F��������
//---------------------------------------------------------------------------
void ITEM_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//ITEM_OBJECT�F�I������
//---------------------------------------------------------------------------
void ITEM_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//ITEM_OBJECT�F�X�V����
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
//ITEM_OBJECT�F�`�揈��
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
