#include <vector>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "hit.h"
#include "chara.h"
#include "move.h"
#include "enemy.h"
#include "effect.h"

//---------------------------------------------------------------------------
//ENEMY_BASE（純粋仮想関数）：コンストラクタ
//---------------------------------------------------------------------------
/*
ENEMY_BASE::ENEMY_BASE(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common) : CHARA_OBJECT(hitdata, enemydata, common) {



}

void ENEMY_BASE::Update() {

	CHARA_OBJECT::Update();
	Loop();

}

*/

//---------------------------------------------------------------------------
//ENEMY1 : グレイナイト
//---------------------------------------------------------------------------
ENEMY1::ENEMY1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common) : CHARA_OBJECT(hitdata, enemydata, common){

	LocalAngle = 0;
	Motion = 0;
	LocalAngleChangeable = true;

}

void ENEMY1::Update() {

	CHARA_OBJECT::Update();

	if (data->islive == false) return;

	if (LocalAngleChangeable == true) {
		if (0 <= data->angle && data->angle <= pi() / 4) LocalAngle = 1;
		if (pi() / 4 < data->angle && data->angle < 3 * pi() / 4) LocalAngle = 0;
		if (3 * pi() / 4 <= data->angle && data->angle <= 5 * pi() / 4) LocalAngle = 3;
		if (5 * pi() / 4 < data->angle && data->angle < 7 * pi() / 4) LocalAngle = 2;
		if (7 * pi() / 4 <= data->angle && data->angle <= 2 * pi()) LocalAngle = 1;
	}

	Think();
	if (data->timer > 320) { 
		data->timer = 0; 
	}

	data->timer++;

}

void ENEMY1::Think() {

		// 0 <= timer < 200 : プレイヤーに旋回→前進
		if (0 <= data->timer && data->timer < 200) {

			if (hit->CalcDistance(common->player->hit) < 800) {
				TurnToPlayer(to_rad(1.0));
				MoveStraight(1.8);

				if (data->timer % 2 == 0) Motion = 1;
				else Motion = 2;
			}

			if (hit->CalcDistance(common->player->hit) < 47.0) {
				FaceForPlayer();
				data->timer = 200;
			}
			
		}

		// timer == 200 : 前方に薙ぎ払い
		else if (data->timer == 200) {

			Motion = 0;

		}

		else if (data->timer == 203) {

			LocalAngleChangeable = false;
			Motion = 3;

		}

		else if (data->timer == 213) {

			CHARA_HIT *hitsword = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(8 + 16, 16), &data->pos, data->angle), Sword_of_GrayKnight);
			CHARA_DEFINFO *sworddata = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(8 + 16, 16), &data->pos, data->angle), data->angle, Sword_of_GrayKnight);
			sword = new BULLET1(hitsword, sworddata, common, this, LocalAngle);
			SummonEnemy(sword);

			Motion = 4;

		}

		else if (data->timer == 218)	Motion = 5;
		else if (data->timer == 223)	Motion = 6;
		else if (data->timer == 228)	Motion = 0, LocalAngleChangeable = true;

	// 200 < timer <= 250 : 停止

}

void ENEMY1::Draw() {

	DrawRectGraph(data->pos.x - 48 - common->camera->GetCameraPos().x, data->pos.y - 48 - common->camera->GetCameraPos().y, 96 * Motion, 96 * LocalAngle, 96, 96, data->GrHandle, true, false);

}

void ENEMY1::Collision() {

	CHARA_OBJECT::Collision();

}

//---------------------------------------------------------------------------
//ENEMY2 : レイトスナイパー
//---------------------------------------------------------------------------
ENEMY2::ENEMY2(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common) : CHARA_OBJECT(hitdata, enemydata, common) {

	LocalAngle = 0;
	Motion = 0;
	LocalAngleChangeable = true;
	c = GetRand(256) * pi() / 128.0;

}

void ENEMY2::Update() {

	CHARA_OBJECT::Update();

	if (data->islive == false) return;

	if (LocalAngleChangeable == true) {
		if (0 <= data->angle && data->angle <= pi() / 4) LocalAngle = 1;
		if (pi() / 4 < data->angle && data->angle < 3 * pi() / 4) LocalAngle = 0;
		if (3 * pi() / 4 <= data->angle && data->angle <= 5 * pi() / 4) LocalAngle = 3;
		if (5 * pi() / 4 < data->angle && data->angle < 7 * pi() / 4) LocalAngle = 2;
		if (7 * pi() / 4 <= data->angle && data->angle <= 2 * pi()) LocalAngle = 1;
	}

	Think();
	if (data->timer > 200) {
		data->timer = 0;
	}
	data->timer++;

}

void ENEMY2::Think() {

	FaceForPlayer();

	//点cに向かって進む
	POINT2D a = Absoluter(&POINT2D(450, 0), &common->player->hit->middle, c);
	POINT2D b = a - hit->middle;
	MoveStr(&VEC2D(b.GetNormal() * 3.0));

	if (b.lengthSq() < 450 * 450) c = c + pi() / (30 + GetRand(60));
	rad_zero(&c);

	if(data->timer == 80){
		bure = (GetRand(100) * pi() / 600) - pi() / 12;
	}

	//定期的に射撃
	if (data->timer == 140 || data->timer == 160 || data->timer == 180) {

		CHARA_HIT *hitbullet = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(12, 0), &data->pos, data->angle+bure), Bullet_of_LateSniper);
		CHARA_DEFINFO *bulletdata = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(12, 0), &data->pos, data->angle+bure), data->angle, Bullet_of_LateSniper);
		CHARA_OBJECT *bullet = new BULLET6(hitbullet, bulletdata, common, this);
		SummonEnemy(bullet);

	}

	if (data->timer < 140) {
		if (data->timer % 30 < 15) Motion = 1;
		else Motion = 2;
	}else{
		if (data->timer % 30 < 15) Motion = 4;
		else Motion = 5;
	}

}

void ENEMY2::Draw() {

	DrawRectGraph(data->pos.x - 48 - common->camera->GetCameraPos().x, data->pos.y - 48 - common->camera->GetCameraPos().y, 96 * Motion, 96 * LocalAngle, 96, 96, data->GrHandle, true, false);

}

void ENEMY2::Collision() {

	CHARA_OBJECT::Collision();

}



//---------------------------------------------------------------------------
//ENEMY3 : ボムスレイヤー
//---------------------------------------------------------------------------
ENEMY3::ENEMY3(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common) : CHARA_OBJECT(hitdata, enemydata, common) {

	

}

void ENEMY3::Update() {

	if (data->islive == false) return;
	Think();

}

void ENEMY3::Think() {



}

void ENEMY3::Collision() {

	CHARA_OBJECT::Collision();

}






//---------------------------------------------------------------------------
//BOSS1: コロナメイジ
//---------------------------------------------------------------------------
BOSS1::BOSS1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common) : CHARA_OBJECT(hitdata, enemydata, common) {

	LocalAngle = 0;
	Motion = 0;
	parge = false;
	extrem = false;
	redd = false;

}

void BOSS1::Update() {

	CHARA_OBJECT::Update();

	if (data->islive == false) return;

	if (0 <= data->angle && data->angle <= pi() / 4) LocalAngle = 1;
	if (pi() / 4 < data->angle && data->angle < 3 * pi() / 4) LocalAngle = 0;
	if (3 * pi() / 4 <= data->angle && data->angle <= 5 * pi() / 4) LocalAngle = 3;
	if (5 * pi() / 4 < data->angle && data->angle < 7 * pi() / 4) LocalAngle = 2;
	if (7 * pi() / 4 <= data->angle && data->angle <= 2 * pi()) LocalAngle = 1;
	

	Think();
	if (data->timer > 1500) {
		data->timer = 0;
	}
	data->timer++;

}

void BOSS1::Think() {

	//追尾2～4秒
	//0.8秒の隙・猶予
	//1.剣
	//2.火放つ
	//3.着火メテオ

	Motion = 0;

	//追尾の時間をランダムに取得
	if (data->timer == 1) {
		pargeDelta = parge;
		if (data->health < 112) parge = true;
		RunTime = GetRand(120) + 120;
		if (pargeDelta != parge) extrem = true;
	}

	//必殺技の準備
	if (extrem == false) {
		//非パージ
		if (redd == false) {
			//追尾
			if (0 <= data->timer && data->timer <= RunTime) {

				TurnToPlayer(to_rad(4.0));
				MoveStraight(2.5);
				if (data->timer % 32 < 16) Motion = 1;
				else Motion = 2;

			}

			//追尾後の行動をランダムに取得
			if (data->timer == RunTime) {
				Action = GetRand(300) % 3;
				//	Action = 2;
			}




			//軸合わせ・プレイヤーの方を向く
			if (data->timer == RunTime) {
				FaceForPlayer();
				data->ChangeAngle(data->angle);
			}

			if (RunTime <= data->timer && data->timer < 84 + RunTime) {
				if (Action == 0)	Motion = 3;
				else if (Action == 1)	Motion = 6;
				else Motion = 8;
			}

			switch (Action) {

			case 0:

				//剣を振る
				if (data->timer >= RunTime + 84 && data->timer < RunTime + 84 + 24) {

					CHARA_DEFINFO *bullet_data;

					double swangle = ((data->timer - (RunTime + 84)) * pi() / 36.0) - (pi() / 3); //時間24fに対して-pi()/3からpi()/3まで変化
					rad_zero(&swangle);

					switch (LocalAngle) {

					case 0:
						bullet_data = mgrp->GetDefaultCharaData(data->pos, pi() / 2 + swangle, Sword_of_CoronaMage);
						break;

					case 1:
						bullet_data = mgrp->GetDefaultCharaData(data->pos, 0 - swangle, Sword_of_CoronaMage);
						break;

					case 2:
						bullet_data = mgrp->GetDefaultCharaData(data->pos, 3 * pi() / 2 + swangle, Sword_of_CoronaMage);
						break;

					default:
						bullet_data = mgrp->GetDefaultCharaData(data->pos, pi() + swangle, Sword_of_CoronaMage);
						break;


					}

					CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(data->pos, Sword_of_CoronaMage);
					CHARA_OBJECT* bullet = new BULLET2(bullet_hit, bullet_data, common, this);
					SummonEnemy(bullet);

				}

				if (data->timer == RunTime + 84 + 24)	data->timer = 0;

				break;

			case 1:
				//衝撃波を放つ
				if (data->timer == RunTime + 84 + 0 || data->timer == RunTime + 84 + 6 || data->timer == RunTime + 84 + 12 || data->timer == RunTime + 84 + 18 || data->timer == RunTime + 84 + 24) {

					FaceForPlayer();
					double wvangle = (GetRand(100) * pi() / 400.0) - (pi() / 8);
					rad_zero(&wvangle);

					CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(16 + 16, 0), &data->pos, data->angle + wvangle), Wave_of_CoronaMage);
					CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(16 + 16, 0), &data->pos, data->angle + wvangle), data->angle, Wave_of_CoronaMage);
					CHARA_OBJECT* bullet = new BULLET3(bullet_hit, bullet_data, common, this);
					SummonEnemy(bullet);

					Motion = 7;

				}

				if (data->timer == RunTime + 84 + 30)	data->timer = 0;

				break;

			case 2:
				//メテオを降らせる
				if (data->timer == RunTime + 84 || data->timer == RunTime + 84 + 30 || data->timer == RunTime + 84 + 60) {

					CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(0, -500), &GetPlayerPos(), 0), Meteor_of_CoronaMage);
					CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(0, -500), &GetPlayerPos(), 0), 3 * pi() / 2, Meteor_of_CoronaMage);
					CHARA_OBJECT* bullet = new BULLET4(bullet_hit, bullet_data, common, this);
					SummonEnemy(bullet);

					Motion = 8;

				}

				if (data->timer == RunTime + 84 + 90)	data->timer = 0;

				break;

			}

		}else{

		//パージ後

		if (0 <= data->timer && data->timer <= RunTime) {

			TurnToPlayer(to_rad(4.0));
			MoveStraight(3.5);
			if (data->timer % 32 < 16) Motion = 1;
			else Motion = 2;

		}

		//追尾後の行動をランダムに取得
		if (data->timer == RunTime) {
			Action = GetRand(300) % 3;
			//	Action = 2;
		}


		//軸合わせ・プレイヤーの方を向く
		if (data->timer == RunTime) {
			FaceForPlayer();
			data->ChangeAngle(data->angle);
		}

		if (RunTime <= data->timer && data->timer < 62 + RunTime) {
			if (Action == 0)	Motion = 3;
			else if (Action == 1)	Motion = 6;
			else Motion = 8;
		}

		switch (Action) {

		case 0:

			//剣を振る
			if (data->timer >= RunTime + 62 && data->timer < RunTime + 62 + 36) {

				CHARA_DEFINFO *bullet_data;

				double swangle = ((data->timer - (RunTime + 62)) * 2*pi() / 36.0) - (2*pi() / 3); //時間24fに対して-pi()/3からpi()/3まで変化
				rad_zero(&swangle);

				switch (LocalAngle) {

				case 0:
					bullet_data = mgrp->GetDefaultCharaData(data->pos, pi() / 2 + swangle, Sword_of_CoronaMage);
					break;

				case 1:
					bullet_data = mgrp->GetDefaultCharaData(data->pos, 0 - swangle, Sword_of_CoronaMage);
					break;

				case 2:
					bullet_data = mgrp->GetDefaultCharaData(data->pos, 3 * pi() / 2 + swangle, Sword_of_CoronaMage);
					break;

				default:
					bullet_data = mgrp->GetDefaultCharaData(data->pos, pi() + swangle, Sword_of_CoronaMage);
					break;


				}

				CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(data->pos, Sword_of_CoronaMage);
				CHARA_OBJECT* bullet = new BULLET2(bullet_hit, bullet_data, common, this);
				SummonEnemy(bullet);

			}

			if (data->timer == RunTime + 62 + 36)	data->timer = 0;

			break;

		case 1:
			//衝撃波を放つ
			if (data->timer >= RunTime + 62 && data->timer <= RunTime + 62 + 100 && data->timer%6 == 0) {

				FaceForPlayer();
				double wvangle = (GetRand(100) * pi() / 300.0) - (pi() / 6);
				rad_zero(&wvangle);

				CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(16 + 16, 0), &data->pos, data->angle + wvangle), Wave_of_CoronaMage);
				CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(16 + 16, 0), &data->pos, data->angle + wvangle), data->angle, Wave_of_CoronaMage);
				BULLET3* bullet = new BULLET3(bullet_hit, bullet_data, common, this);
				SummonEnemy(bullet);

				Motion = 7;

			}

			if (data->timer == RunTime + 62 + 110)	data->timer = 0;

			break;

		case 2:
			if (data->timer == RunTime + 62) playerposm = GetPlayerPos();
			//メテオを降らせる
			if (data->timer >= RunTime + 62 && data->timer <= RunTime + 62 + 42 && data->timer%6 == 0) {

				int mx = GetRand(200);
				int my = GetRand(200);

				CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(Absoluter(&POINT2D(-100+mx, -600+my), &playerposm, 0), Meteor_of_CoronaMage);
				CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(Absoluter(&POINT2D(-100+mx, -600+my), &playerposm, 0), 3 * pi() / 2, Meteor_of_CoronaMage);
				CHARA_OBJECT* bullet = new BULLET4(bullet_hit, bullet_data, common, this);
				SummonEnemy(bullet);

				Motion = 8;

			}

			if (data->timer == RunTime + 62 + 50)	data->timer = 0;

			break;

		}

		}

	}
	else {

		//必殺メテオ

		if (0 <= data->timer && data->timer < 70) {
			data->deffence = 100;
			Motion = 8;
			redd = true;
		}
		if (70 <= data->timer && data->timer <= 180) {
			Motion = 9;
		}
		if (data->timer >= 180 && data->timer < 780) {
			Motion = 9;

			if (data->timer % 6 == 0) {

				int mx = GetRand(1280);
				int my = GetRand(720);

				CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(POINT2D(mx, my - 500), Meteor_of_CoronaMage);
				CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(POINT2D(mx, my - 500), 3 * pi() / 2, Meteor_of_CoronaMage);
				CHARA_OBJECT* bullet = new BULLET4(bullet_hit, bullet_data, common, this);
				SummonEnemy(bullet);

			}

		}
		if (data->timer == 780) {
			data->deffence = 30.0;
			data->timer = 0;
			extrem = false;
		}

	}


}

void BOSS1::Collision() {

	CHARA_OBJECT::Collision();

}

void BOSS1::Draw() {

	DrawRectGraph(data->pos.x - 48 - common->camera->GetCameraPos().x, data->pos.y - 48 - common->camera->GetCameraPos().y, 96 * Motion, 96 * LocalAngle, 96, 96, data->GrHandle, true, false);

	if (redd == true) {

		if (extrem == true) {
			if (70 <= data->timer && data->timer < 180) {

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (data->timer - 70) * 0.5);
				DrawBox(0, 0, 800, 600, GetColor(255, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}
			else if (180 <= data->timer) {

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 55);
				DrawBox(0, 0, 800, 600, GetColor(255, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}
		}
		else {

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 55);
			DrawBox(0, 0, 800, 600, GetColor(255, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}

	}

}











//グレイナイトが振る剣
BULLET1::BULLET1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent, int locangle) : CHARA_OBJECT(hitdata, enemydata, common) {
	
	this->parent = parent;
	LocalAngle = locangle;

}

void BULLET1::Update() {

	CHARA_OBJECT::Update();

	if (data->islive == false) return;

	Think();
	if (parent->data->islive == false) Kill();
	if (data->timer > 15) {
		data->islive = 0; 
		Kill();
	}

	

	data->timer++;

}

void BULLET1::Think() {

	if (0 <= data->timer && data->timer <= 4) {

		ChangeHitObject(10);

		switch (LocalAngle) {

		case 0:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, pi() / 2));
			break;

		case 1:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, 0));
			break;

		case 2:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, 3* pi()/2));
			break;

		case 3:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, pi()));
			break;

		}

	}
	else if (5 <= data->timer && data->timer <= 9) {

		ChangeHitObject(16);

		switch (LocalAngle) {

		case 0:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, pi() / 2));
			break;

		case 1:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, 0));
			break;

		case 2:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, 3* pi()/ 2));
			break;

		case 3:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos,  pi()));
			break;

		}

	}
	else if (10 <= data->timer && data->timer <= 14) {

		ChangeHitObject(10);

		switch (LocalAngle) {

		case 0:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, pi() / 2));
			break;

		case 1:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, 0));
			break;

		case 2:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, 3*pi()/2));
			break;

		case 3:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, pi()));
			break;

		}

	}


}

void BULLET1::Collision() {

	CHARA_OBJECT::Collision();

	if (hit->HitCheckOnMove(common->player->hit)) {

		if(common->player->Damage(6, false) != 0) EffectWith(RedEffect, common->player->hit);
		common->player->KnockBack(&ConvertForVector2(20.0, data->angle));

	}

}



//プレイヤーが振る剣
PLAYER_SWORD::PLAYER_SWORD(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent, int locangle) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	LocalAngle = locangle;

}

void PLAYER_SWORD::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();
	//	data->ChangePos(data->pos + data->move);
	if (parent->data->islive == 0) {
		Kill();
		return;
	}

	if (data->timer > 9) {
		data->islive = 0;
		Kill();
	}
	data->timer++;

}

void PLAYER_SWORD::Think() {

	if (0 <= data->timer && data->timer <= 2) {

			ChangeHitObject(10);

			switch (LocalAngle) {

			case 0:			
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, pi()/2));
				break;

			case 1:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, 0));
				break;

			case 2:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, pi()));
				break;

			case 3:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, 3*pi()/2));
				break;

			}

	}
	else if (3 <= data->timer && data->timer <= 5) {

			ChangeHitObject(16);

			switch (LocalAngle) {

			case 0:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, pi() / 2));
				break;

			case 1:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, 0));
				break;

			case 2:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, pi()));
				break;

			case 3:
				MoveStrTo(&Absoluter(&POINT2D(16 + 16, 0), &parent->data->pos, 3 * pi() / 2));
				break;

			}

	}
	else if (6 <= data->timer && data->timer <= 8) {

		ChangeHitObject(10);

		switch (LocalAngle) {

		case 0:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, pi() / 2));
			break;

		case 1:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, 32), &parent->data->pos, 0));
			break;

		case 2:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, pi()));
			break;

		case 3:
			MoveStrTo(&Absoluter(&POINT2D(16 + 16, -32), &parent->data->pos, 3 * pi() / 2));
			break;

		}

	}

	
}

void PLAYER_SWORD::Collision() {

	CHARA_OBJECT::Collision();

	//charaのなかでEnemy,Bulletのものについて
	//衝突判定が重なってればダメージ
	for (auto itr = common->chara->chara->begin(); itr != common->chara->chara->end(); itr++) {

		if ((*itr)->data->charamem == Enemy_mem || (*itr)->data->charamem == Bullet_mem || (*itr)->data->charamem == Boss_mem) {

			if ((*itr) != this) {

				if (hit->HitCheckOnMove((*itr)->hit)) {

					if ((*itr)->Damage(6, false) != 0) EffectWith(GreenEffect, (*itr)->hit);

				}

			}

		}

	}

}



//---------------------------------------------------------------------------
//BULLET2: コロナメイジの剣
//---------------------------------------------------------------------------
BULLET2::BULLET2(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;

}

void BULLET2::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}
	if (data->timer > 6) Kill();

	data->timer++;

}

void BULLET2::Think() {

	MoveStraight(34.0);

}

void BULLET2::Collision() {

	CHARA_OBJECT::Collision();

	if (hit->HitCheckOnMove(common->player->hit)) {

		if (common->player->Damage(8, false) != 0) EffectWith(ExplosionEffect, common->player->hit);;
		common->player->KnockBack(&ConvertForVector2(20.0, data->angle));

	}

}

void BULLET2::Draw() {

	//DrawRectGraph(data->pos.x - 8 - common->camera->GetCameraPos().x, data->pos.y - 8 - common->camera->GetCameraPos().y, 0, 0, 16, 16, data->GrHandle, true, false);
	DrawRectExtendGraph(data->pos.x - 16 - common->camera->GetCameraPos().x, data->pos.y - 16 - common->camera->GetCameraPos().y, data->pos.x + 16 - common->camera->GetCameraPos().x, data->pos.y + 16 - common->camera->GetCameraPos().y, 0, 0, 16, 16, data->GrHandle, true);
}



//---------------------------------------------------------------------------
//BULLET3: コロナメイジの衝撃派
//---------------------------------------------------------------------------
BULLET3::BULLET3(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	accel = 0;

}

void BULLET3::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}
	if (data->timer > 90) Kill();

	data->timer++;

}

void BULLET3::Think() {

	MoveStraight(accel + 0.8);
	accel = accel + 0.8;

}

void BULLET3::Collision() {

	CHARA_OBJECT::Collision();

	if (hit->HitCheckOnMove(common->player->hit)) {

		if (common->player->Damage(5, false) != 0) EffectWith(ExplosionEffect, common->player->hit);;
		common->player->KnockBack(&ConvertForVector2(20.0, data->angle));

	}

}

void BULLET3::Draw() {

	DrawRotaGraph(data->pos.x - 16 - common->camera->GetCameraPos().x, data->pos.y - 16 - common->camera->GetCameraPos().y, 1.0, 2*pi() - data->angle, data->GrHandle, true);

}

//---------------------------------------------------------------------------
//BULLET4: コロナメイジのメテオ
//---------------------------------------------------------------------------
BULLET4::BULLET4(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	data->timer = 0;

}

void BULLET4::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}

	if (data->timer > 3700) Kill();

	data->timer++;

}

void BULLET4::Think() {

	FaceForPlayer();

	if (data->timer == 0) {

		CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(POINT2D(data->pos.x, data->pos.y + 500), Shadow_of_meteor);
		CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(POINT2D(data->pos.x, data->pos.y + 500), 0, Shadow_of_meteor);
		CHARA_OBJECT* bullet = new SHADOW1(bullet_hit, bullet_data, common, parent);
		SummonEnemy(bullet);

	}

	//落ちる
	if (data->timer < 50) {
		MoveStr(&VEC2D(0, 10.0));
	}
	//爆発
	if (data->timer == 50) {
		
		CHARA_HIT* bullet_hit = mgrp->GetDefaultCharaHit(data->pos, Explosion_of_meteor);
		CHARA_DEFINFO *bullet_data = mgrp->GetDefaultCharaData(data->pos, 0, Explosion_of_meteor);
		CHARA_OBJECT* bullet = new BULLET5(bullet_hit, bullet_data, common, parent);
		SummonEnemy(bullet);

		data->GrHandle = mgrp->GetGrHandle(6);

	}
	//60秒残り続ける
	if (data->timer > 50) {

		

	}

}

void BULLET4::Collision() {

	CHARA_OBJECT::Collision();


	if (data->timer > 50) {

		if (hit->HitCheckOnMove(common->player->hit)) {

			if (common->player->Damage(5, false) != 0) EffectWith(ExplosionEffect, common->player->hit);
			common->player->KnockBack(&ConvertForVector2(5.0, data->angle));

		}

	}

}

void BULLET4::Draw() {

	if (data->timer < 50) {
		DrawRectGraph(data->pos.x - 16 - common->camera->GetCameraPos().x, data->pos.y - 16 - common->camera->GetCameraPos().y, 0, 0, 32, 32, data->GrHandle, true, false);
	}


	else {
		int b = (data->timer % 30) / 10;
		DrawRectGraph(data->pos.x - 16 - common->camera->GetCameraPos().x, data->pos.y - 16 - common->camera->GetCameraPos().y, 32*b, 0, 32, 32, data->GrHandle, true, false);
	}

}


//---------------------------------------------------------------------------
//BULLET5: メテオの爆発
//---------------------------------------------------------------------------
BULLET5::BULLET5(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	rad = 1;

}

void BULLET5::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (data->timer > 20) Kill();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}

	data->timer++;

}

void BULLET5::Think() {

	FaceForPlayer();

	if (data->timer < 10) {
		rad += 8;
	}
	else {
		rad -= 8;
	}

	ChangeHitObject(rad);

}

void BULLET5::Collision() {

	CHARA_OBJECT::Collision();

	if (hit->HitCheckOnMove(common->player->hit)) {

		if(common->player->Damage(12, false) != 0) EffectWith(ExplosionEffect, common->player->hit);
		common->player->KnockBack(&ConvertForVector2(20.0, data->angle));

	}

}

void BULLET5::Draw() {

	DrawCircleAA(data->pos.x - common->camera->GetCameraPos().x, data->pos.y - common->camera->GetCameraPos().y, rad, 32, GetColor(255, 0, 0), true);

}



//---------------------------------------------------------------------------
//BULLET6: レイトスナイパーの弾
//---------------------------------------------------------------------------
BULLET6::BULLET6(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	data->timer = 0;

}

void BULLET6::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}

	if (data->timer > 120) Kill();

	data->timer++;

}

void BULLET6::Think() {

	MoveStraight(9.0);

}

void BULLET6::Collision() {

	CHARA_OBJECT::Collision();

	if (hit->HitCheckOnMove(common->player->hit)) {

		if (common->player->Damage(2, false) != 0) EffectWith(ExplosionEffect, common->player->hit);
		common->player->KnockBack(&ConvertForVector2(8.0, data->angle));
		Kill();

	}

	if (hit->isHitWall == true) {

		Effect(ExplosionEffect, &data->pos);
		Kill();

	}

}

void BULLET6::Draw() {

	DrawRotaGraph(data->pos.x - 8 - common->camera->GetCameraPos().x, data->pos.y - 8 - common->camera->GetCameraPos().y, 1.0, 2*pi() - data->angle, data->GrHandle, true);

}



//---------------------------------------------------------------------------
//SHADOW1:
//---------------------------------------------------------------------------
SHADOW1::SHADOW1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent) : CHARA_OBJECT(hitdata, enemydata, common) {

	this->parent = parent;
	data->timer = 0;

}

void SHADOW1::Update() {

	CHARA_OBJECT::Update();
	if (data->islive == false) return;
	Think();

	if (parent->data->islive == 0) {
		Kill();
		return;
	}

	if (data->timer > 50) Kill();

	data->timer++;

}

void SHADOW1::Think() {



}

void SHADOW1::Collision() {

	CHARA_OBJECT::Collision();

}

void SHADOW1::Draw() {

	DrawGraph(data->pos.x - 8 - common->camera->GetCameraPos().x, data->pos.y - 8 - common->camera->GetCameraPos().y, data->GrHandle, true);

}