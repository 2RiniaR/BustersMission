#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "camera.h"

class COMMON_DATA;
class ITEM_OBJECT;

enum ItemType {

	Health5,
	Health10,
	Score10,
	Score20,
	SpeedUp1,
	StrengthUp1,
	DeffenceUp1

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラのマネージャークラス
//---------------------------------------------------------------------------
class ITEM_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	std::list<ITEM_OBJECT*> *item;
	std::list<int> *reset;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	ITEM_OBJMGR(COMMON_DATA *common);	//コンストラクタ

	void AddItem(ITEM_OBJECT *itemdata);	//敵を追加する
	void RemoveItem(int itrnum);	//敵を削除する

	void GetDefaultItem(ITEM_OBJECT *enemy, int type);

private:
	void ResetListElement();

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラ（抽象クラス）
//---------------------------------------------------------------------------
class ITEM_OBJECT : public BASE_OBJECT {

public:

	//■■■メンバ変数■■■
	int itrnum;
	ITEM_OBJMGR *mgrp;
	int timer;
	ItemType type;
	CHARA_HIT *hit;
	POINT2D pos;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Collision();
	void Draw();		//描画処理
	void InputItr(int itrnum);
	void InputMgr(ITEM_OBJMGR *mgrpointer);
	void RemoveForList();
	ITEM_OBJECT(ItemType type, POINT2D pos, double size, COMMON_DATA *common);		//コンストラクタ
	~ITEM_OBJECT();	//デストラクタ

};
