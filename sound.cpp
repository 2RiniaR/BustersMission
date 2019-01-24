#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "hit.h"
#include "sound.h"

using namespace std;

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F�R���X�g���N�^
//---------------------------------------------------------------------------
SOUND_OBJMGR::SOUND_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	sound = new std::list<SOUND_OBJECT>;
	reset = new std::list<int>;

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F��������
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Initialize() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Initialize();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F�I������
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Finalize() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F�X�V����
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Update() {

	int i = 0;

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->InputItr(i);
			itr->Update();
			i++;
		}
	}

	//�폜���X�greset�ɓ����Ă���e�f�[�^���ꊇ�폜
	if (reset->empty() == false) {

		reset->sort();
		auto itr_reset = reset->begin();
		i = 0;

		for (auto itr = sound->begin(); itr != sound->end();) {

			if (*itr_reset == i) {

				itr = sound->erase(itr);
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
//SOUND_OBJMGR�F�`�揈��
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Draw() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F�G��ǉ�����
//---------------------------------------------------------------------------
void SOUND_OBJMGR::AddSound(int type) {

	sound->emplace_back(type, common, sound->size());

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR�F�G���폜����
//---------------------------------------------------------------------------
void SOUND_OBJMGR::RemoveSound(int itrnum) {

	reset->push_back(itrnum);	//�폜���X�greset�ɓo�^

}










//---------------------------------------------------------------------------
//SOUND_OBJECT�F�C�j�V�����C�U
//---------------------------------------------------------------------------
SOUND_OBJECT::SOUND_OBJECT(int type, COMMON_DATA *common, int itrnum) {

	this->common = common;
	this->type = type;
	itr = itrnum;

}

//---------------------------------------------------------------------------
//SOUND_OBJECT�F�f�X�g���N�^
//---------------------------------------------------------------------------
SOUND_OBJECT::~SOUND_OBJECT() {}

//---------------------------------------------------------------------------
//SOUND_OBJECT�F��������
//---------------------------------------------------------------------------
void SOUND_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//SOUND_OBJECT�F�I������
//---------------------------------------------------------------------------
void SOUND_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//SOUND_OBJECT�F�X�V����
//---------------------------------------------------------------------------
void SOUND_OBJECT::Update() {



}

//---------------------------------------------------------------------------
//SOUND_OBJECT�F�`�揈��
//---------------------------------------------------------------------------
void SOUND_OBJECT::Draw() {



}

void SOUND_OBJECT::InputItr(int itrnum) {

	itr = itrnum;

}
