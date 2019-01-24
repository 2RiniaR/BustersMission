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
//SOUND_OBJMGR：コンストラクタ
//---------------------------------------------------------------------------
SOUND_OBJMGR::SOUND_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	sound = new std::list<SOUND_OBJECT>;
	reset = new std::list<int>;

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR：初期処理
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Initialize() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Initialize();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR：終了処理
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Finalize() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR：更新処理
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

	//削除リストresetに入っている弾データを一括削除
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
//SOUND_OBJMGR：描画処理
//---------------------------------------------------------------------------
void SOUND_OBJMGR::Draw() {

	if (sound->empty() == false) {
		for (auto itr = sound->begin(); itr != sound->end(); ++itr) {
			itr->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR：敵を追加する
//---------------------------------------------------------------------------
void SOUND_OBJMGR::AddSound(int type) {

	sound->emplace_back(type, common, sound->size());

}

//---------------------------------------------------------------------------
//SOUND_OBJMGR：敵を削除する
//---------------------------------------------------------------------------
void SOUND_OBJMGR::RemoveSound(int itrnum) {

	reset->push_back(itrnum);	//削除リストresetに登録

}










//---------------------------------------------------------------------------
//SOUND_OBJECT：イニシャライザ
//---------------------------------------------------------------------------
SOUND_OBJECT::SOUND_OBJECT(int type, COMMON_DATA *common, int itrnum) {

	this->common = common;
	this->type = type;
	itr = itrnum;

}

//---------------------------------------------------------------------------
//SOUND_OBJECT：デストラクタ
//---------------------------------------------------------------------------
SOUND_OBJECT::~SOUND_OBJECT() {}

//---------------------------------------------------------------------------
//SOUND_OBJECT：初期処理
//---------------------------------------------------------------------------
void SOUND_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//SOUND_OBJECT：終了処理
//---------------------------------------------------------------------------
void SOUND_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//SOUND_OBJECT：更新処理
//---------------------------------------------------------------------------
void SOUND_OBJECT::Update() {



}

//---------------------------------------------------------------------------
//SOUND_OBJECT：描画処理
//---------------------------------------------------------------------------
void SOUND_OBJECT::Draw() {



}

void SOUND_OBJECT::InputItr(int itrnum) {

	itr = itrnum;

}
