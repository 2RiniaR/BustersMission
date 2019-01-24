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

	void MoveStraight(double speed);	//���݌����Ă��������speed�̑��x�Ői��

	void MoveStr(VEC2D *direction, double speed);	//direction�̕�����speed/F�ňړ�
	void MoveStr(POINT2D *position, double speed);
	void MoveStr(VEC2D *direction, int flame);
	void MoveStr(POINT2D *position, int flame);

	void MoveAngleDeg(double deg, double speed);			//speed/F�̑��x��dig(�����v��肪��)������]
	void MoveAngleDeg(double deg, int flame);
	void MoveToAngleDeg(double deg, double speed);
	void MoveToAngleDeg(double deg, int flame);
	void MoveAngleRad(double rad, double speed);			//speed/F�̑��x��dig(�����v��肪��)������]
	void MoveAngleRad(double rad, int flame);
	void MoveToAngleRad(double rad, double speed);
	void MoveToAngleRad(double rad, int flame);

	void GetPlayerPos(POINT2D *position);				//Player�̍��W���擾
	void Warp(const POINT2D &position);					//position�̍��W�Ƀ��[�v
	void HomingToPlayer(double speed);		//Player��speed/F�Œǔ�
	void TurnToPlayer(double homing);	//homing�̑��x��Player�ɐ���
	void Disappering();			//���ł���
	void SetStatusEffect(StatusEffect effect, int flag);

	void SummonEnemy(int type);			//enemy������
	void SummonEnemy(ENEMY_BASE *enemydata);

	void SummonBullet();		//bullet������
	VEC2D AngleToVector(double angle);
	void ChangeHitObject(HIT_OBJECT *hit);

};

*/