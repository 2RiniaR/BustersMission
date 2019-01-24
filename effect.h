#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "camera.h"

class COMMON_DATA;
class EFFECT_OBJECT;

enum EffectType {

	GreenEffect,
	RedEffect,
	ExplosionEffect

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラのマネージャークラス
//---------------------------------------------------------------------------
class EFFECT_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	std::list<EFFECT_OBJECT*> *effect;
	std::list<int> *reset;
	std::vector<int> *GrHandle;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	EFFECT_OBJMGR(COMMON_DATA *common);	//コンストラクタ

	void AddEffect(EFFECT_OBJECT *effectdata);	//敵を追加する
	void RemoveEffect(int itrnum);	//敵を削除する

	void GetDefaultEffect(EFFECT_OBJECT *enemy, int type, POINT2D *pos);
	void InitGr();
	int GetGrHandle(int a) { return GrHandle->at(a); };

private:
	void ResetListElement();

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラ（抽象クラス）
//---------------------------------------------------------------------------
class EFFECT_OBJECT : public BASE_OBJECT {

public:

	//■■■メンバ変数■■■
	int itrnum;
	EFFECT_OBJMGR *mgrp;
	int timer;
	POINT2D pos;
	EffectType type;
	int GrHandle;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	void InputItr(int itrnum);
	void InputMgr(EFFECT_OBJMGR *mgrpointer);
	void RemoveForList();
	EFFECT_OBJECT(EffectType type, int ofset, COMMON_DATA *common, POINT2D *pos);		//コンストラクタ
	~EFFECT_OBJECT();	//デストラクタ

};
