#pragma once

#include "gclass.h"
#include "chara.h"
#include "hit.h"

class COMMON_DATA;
class CHARA_OBJECT;

//---------------------------------------------------------------------------
//ゲームオブジェクト：プレイヤー
//---------------------------------------------------------------------------
class PLAYER_OBJECT : public CHARA_OBJECT{

public:

	//■■■メンバ変数■■■
	CHARA_OBJECT *sword;
	int swordcool;
	int LocalAngle;
	int Motion;
	int WalkTime;
	bool isWalk;
	bool LocalAngleChangeable;

	int DamageSound;
	int SwingSound;

	//■■■メンバ関数■■■
	void Initialize() override;
	void Finalize() override;
	void Update() override;		//更新処理
	void Collision();
	void Draw() override;		//描画処理
	void UpdateMotion();
	PLAYER_OBJECT(CHARA_HIT *hitdata, CHARA_DEFINFO *data, COMMON_DATA *common);

	POINT2D GetPlayerPos() { return data->pos; };
	void SwingSword();

};
