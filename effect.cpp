#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "effect.h"

using namespace std;

//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F�R���X�g���N�^
//---------------------------------------------------------------------------
EFFECT_OBJMGR::EFFECT_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	common->effect = this;
	effect = new std::list<EFFECT_OBJECT*>;
	reset = new std::list<int>;
	GrHandle = new std::vector<int>;

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F��������
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
//EFFECT_OBJMGR�F�I������
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Finalize() {

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F�X�V����
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

	//�폜���X�greset�ɓ����Ă���L�����f�[�^���ꊇ�폜
	ResetListElement();

}


//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F�`�揈��
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::Draw() {

	if (effect->empty() == false) {
		for (auto itr = effect->begin(); itr != effect->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F�G��ǉ�����
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::AddEffect(EFFECT_OBJECT *effectdata) {

	effect->push_back(effectdata);
	effectdata->InputItr(effect->size());
	effectdata->InputMgr(this);

}

//---------------------------------------------------------------------------
//EFFECT_OBJMGR�F�G���폜����
//---------------------------------------------------------------------------
void EFFECT_OBJMGR::RemoveEffect(int itrnum) {

	reset->push_back(itrnum);	//�폜���X�greset�ɓo�^

}

void EFFECT_OBJMGR::InitGr() {

	GrHandle->push_back(LoadGraph("data/image/effect/effect1.png"));		// 0
	GrHandle->push_back(LoadGraph("data/image/effect/effect2.png"));		// 1
	GrHandle->push_back(LoadGraph("data/image/effect/effect3.png"));		// 2

}


void EFFECT_OBJMGR::ResetListElement() {

	//�폜���X�greset�ɓ����Ă���L�����f�[�^���ꊇ�폜
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
//EFFECT_OBJECT�F�C�j�V�����C�U
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
//EFFECT_OBJECT�F�f�X�g���N�^
//---------------------------------------------------------------------------
EFFECT_OBJECT::~EFFECT_OBJECT() {

	

}

//---------------------------------------------------------------------------
//EFFECT_OBJECT�F��������
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//EFFECT_OBJECT�F�I������
//---------------------------------------------------------------------------
void EFFECT_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//EFFECT_OBJECT�F�X�V����
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
//EFFECT_OBJECT�F�`�揈��
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
