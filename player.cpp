#include "DxLib.h"
#include "sceneMGR.h"
#include "key.h"
#include "game.h"
#include "hit.h"
#include "player.h"
#include "gclass.h"
#include "chara.h"
#include "enemy.h"

//---------------------------------------------------------------------------
//イニシャライザ
//---------------------------------------------------------------------------
PLAYER_OBJECT::PLAYER_OBJECT(CHARA_HIT *hitdata, CHARA_DEFINFO *data, COMMON_DATA *common) : CHARA_OBJECT(hitdata, data, common) {

	common->player = this;
	data->charatype = Player;
	LocalAngle = 0;
	Motion = 0;
	WalkTime = 0;
	isWalk = false;
	LocalAngleChangeable = true;

}

//---------------------------------------------------------------------------
//初期処理
//---------------------------------------------------------------------------
void PLAYER_OBJECT::Initialize() {

	CHARA_OBJECT::Initialize();

}

//---------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------
void PLAYER_OBJECT::Finalize() {

	CHARA_OBJECT::Finalize();

}

//---------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------
void PLAYER_OBJECT::Update() {

	isWalk = false;

	CHARA_OBJECT::Update();

	if (data->health <= 0) data->islive = false;

	swordcool--;
	if (swordcool < 0) swordcool = 0;

	if (swordcool >= 1) LocalAngleChangeable = false;
	else LocalAngleChangeable = true;


	if (data->KnockBackTime == 0) {

		if (common->key->GetJoypadAmount() == 0) {

			if (common->key->GetKeyStatus(KEY_INPUT_UP) >= 1) { //↑キーが押されたら

				if (common->key->GetKeyStatus(KEY_INPUT_LEFT) >= 1 || common->key->GetKeyStatus(KEY_INPUT_RIGHT) >= 1) { data->move.y -= data->speed * 0.7071; }
				else { data->move.y -= data->speed; }
				isWalk = true;
				if (LocalAngleChangeable == true) LocalAngle = 0;

			}

			if (common->key->GetKeyStatus(KEY_INPUT_DOWN) >= 1) { //↓キーが押されたら

				if (common->key->GetKeyStatus(KEY_INPUT_LEFT) >= 1 || common->key->GetKeyStatus(KEY_INPUT_RIGHT) >= 1) { data->move.y += data->speed * 0.7071; }
				else { data->move.y += data->speed; }
				isWalk = true;
				if (LocalAngleChangeable == true) LocalAngle = 3;

			}

			if (common->key->GetKeyStatus(KEY_INPUT_LEFT) >= 1) { //←キーが押されたら

				if (common->key->GetKeyStatus(KEY_INPUT_UP) >= 1 || common->key->GetKeyStatus(KEY_INPUT_DOWN) >= 1) { data->move.x -= data->speed * 0.7071; }
				else { data->move.x -= data->speed; }
				isWalk = true;
				if (LocalAngleChangeable == true) LocalAngle = 2;

			}

			if (common->key->GetKeyStatus(KEY_INPUT_RIGHT) >= 1) { //→キーが押されたら

				if (common->key->GetKeyStatus(KEY_INPUT_UP) >= 1 || common->key->GetKeyStatus(KEY_INPUT_DOWN) >= 1) { data->move.x += data->speed * 0.7071; }
				else {
					data->move.x += data->speed;
				}
				isWalk = true;
				if (LocalAngleChangeable == true) LocalAngle = 1;


			}

			if (common->key->GetKeyStatus(KEY_INPUT_Z) == 1) {

				if (swordcool == 0) {
					swordcool = 12;
				}

			}

		}
		else {

			VEC2D an = VEC2D(common->key->Ax / 1000.0, common->key->Ay / 1000.0);

			VEC2D mv = VEC2D(data->speed * an.x, data->speed * an.y);
			if(an.length() > 1.0) mv = mv / an.length();
			data->move = data->move + mv;

		//	data->move.x += data->speed * common->key->Ax / 1000.0;
		//	data->move.y += data->speed * common->key->Ay / 1000.0;

			double ag, rg;

			ConvertForAngleRadius(&data->move, &rg, &ag);

			if (LocalAngleChangeable == true) {
				if (0 <= ag && ag <= pi() / 4) LocalAngle = 1;
				if (pi() / 4 < ag && ag < 3 * pi() / 4) LocalAngle = 0;
				if (3 * pi() / 4 <= ag && ag <= 5 * pi() / 4) LocalAngle = 2;
				if (5 * pi() / 4 < ag && ag < 7 * pi() / 4) LocalAngle = 3;
				if (7 * pi() / 4 <= ag && ag <= 2 * pi()) LocalAngle = 1;
			}

			if (common->key->GetKeyStatus(KEY_INPUT_Z) == 1) {

				if (swordcool == 0) {
					swordcool = 12;
				}

			}

		}

	}

	if (isWalk == true) WalkTime++;
	else WalkTime = 0;

	if(swordcool == 10) SwingSword();

	UpdateMotion();

}

void PLAYER_OBJECT::UpdateMotion() {

	if (data->move.x == 0 && data->move.y == 0) Motion = 0;	//静止状態
	if ((WalkTime / 15) % 2 == 0) Motion = 1;				//歩き１
	if ((WalkTime / 15) % 2 == 1) Motion = 2;				//歩き２
	if (swordcool > 10) Motion = 3;
	if (8 <= swordcool && swordcool <= 10) Motion = 4;
	if (5 <= swordcool && swordcool <= 7) Motion = 5;
	if (2 <= swordcool && swordcool <= 4) Motion = 6;
	if (data->KnockBackTime > 0) Motion = 7;				//ノックバック中

}

void PLAYER_OBJECT::Collision() {

	CHARA_OBJECT::Collision();

}

//---------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------
void PLAYER_OBJECT::Draw() {

	//CHARA_OBJECT::Draw();
	//DrawCircleAA(data->pos.x - common->camera->GetCameraPos().x, data->pos.y - common->camera->GetCameraPos().y, 16.0, 32, GetColor(0,0,255), TRUE);	//自機の位置に円を描画
	DrawRectGraph(data->pos.x-48 - common->camera->GetCameraPos().x, data->pos.y-48 - common->camera->GetCameraPos().y, 96 * Motion, 96 * LocalAngle, 96, 96, data->GrHandle, true, false);

}


void PLAYER_OBJECT::SwingSword() {
	
	CHARA_HIT *hitsword = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(8 + 16, 16), &data->pos, data->angle), Sword_of_Player);
	CHARA_DEFINFO *sworddata = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(8 + 16, 16), &data->pos, data->angle), 0.0, Sword_of_Player);
	sword = new PLAYER_SWORD(hitsword, sworddata, common, this, LocalAngle);
	SummonEnemy(sword);

}