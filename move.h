#pragma once
/*
#include "hit.h"

class CHARA_OBJECT;
class CHARA_OBJMGR;
class CHARA_DEFINFO;
class ENEMY_BASE;
class COMMON_DATA;
class HIT_OBJECT;

enum StatusEffect;

class ENEMY_DEFMOVE {

public:
	CHARA_OBJMGR *mgr;
	CHARA_OBJECT *obj;
	COMMON_DATA *common;

protected:

	void MoveStraight(double speed);	//現在向いている方向にspeedの速度で進む

	void MoveStr(VEC2D *direction, double speed);	//directionの方向にspeed/Fで移動
	void MoveStr(POINT2D *position, double speed);
	void MoveStr(VEC2D *direction, int flame);
	void MoveStr(POINT2D *position, int flame);

	void MoveAngleDeg(double deg, double speed);			//speed/Fの速度でdig(反時計回りが正)だけ回転
	void MoveAngleDeg(double deg, int flame);
	void MoveToAngleDeg(double deg, double speed);
	void MoveToAngleDeg(double deg, int flame);
	void MoveAngleRad(double rad, double speed);			//speed/Fの速度でdig(反時計回りが正)だけ回転
	void MoveAngleRad(double rad, int flame);
	void MoveToAngleRad(double rad, double speed);
	void MoveToAngleRad(double rad, int flame);

	void GetPlayerPos(POINT2D *position);				//Playerの座標を取得
	void Warp(const POINT2D &position);					//positionの座標にワープ
	void HomingToPlayer(double speed);		//Playerをspeed/Fで追尾
	void TurnToPlayer(double homing);	//homingの速度でPlayerに旋回
	void Disappering();			//消滅する
	void SetStatusEffect(StatusEffect effect, int flag);

	void SummonEnemy(int type);			//enemyを召喚
	void SummonEnemy(ENEMY_BASE *enemydata);

	void SummonBullet();		//bulletを召喚
	VEC2D AngleToVector(double angle);
	void ChangeHitObject(HIT_OBJECT *hit);

};

*/