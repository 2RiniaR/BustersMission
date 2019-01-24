#pragma once
#include <vector>
#include <list>

#include "gclass.h"

class SOUND_OBJECT;
class COMMON_DATA;
class HIT_OBJECT;

//---------------------------------------------------------------------------
//弾オブジェクト：弾のマネージャークラス
//---------------------------------------------------------------------------
class SOUND_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	COMMON_DATA * common;
	std::list<SOUND_OBJECT> *sound;
	std::list<int> *reset;
	int i; //カウンタ変数

		   //■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	SOUND_OBJMGR(COMMON_DATA *common);	//コンストラクタ

	void AddSound(int type);	//敵を追加する
	void RemoveSound(int itrnum);	//敵を削除する

};

//---------------------------------------------------------------------------
//弾オブジェクト：弾
//---------------------------------------------------------------------------
class SOUND_OBJECT : public BASE_OBJECT {

public:

	//■■■メンバ変数■■■
	HIT_OBJECT * hit;	//衝突判定オブジェクトのデータ
	int type;
	COMMON_DATA *common;
	int itr;
	SOUND_OBJMGR *mgr;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	void InputItr(int itrnum);
	SOUND_OBJECT(int type, COMMON_DATA *common, int itrnum);		//コンストラクタ
	~SOUND_OBJECT();	//デストラクタ

};
