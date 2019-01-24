#include <vector>
#include <cmath>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "hit.h"
#include "chara.h"
#include "enemy.h"
#include "effect.h"
#include "move.h"

void CHARA_OBJECT::MoveStraight(double speed) {
	data->move = data->move + (AngleToVector(data->angle) * (float)speed);
}

//direction�̕�����speed/F�ňړ�
void CHARA_OBJECT::MoveStr(VEC2D *direction) {
	data->move = data->move + *direction;
}

void CHARA_OBJECT::MoveStrTo(POINT2D *position) {
	VEC2D direction = VEC2D(*position - data->pos);
	MoveStr(&direction);
}

void CHARA_OBJECT::MoveStr(VEC2D *direction, int flame) {

}

void CHARA_OBJECT::MoveStr(POINT2D *position, int flame) {

}

//speed/F�̑��x��dig(�����v��肪��)������]
void CHARA_OBJECT::MoveAngleDeg(double deg, double speed) {

}

void CHARA_OBJECT::MoveAngleDeg(double deg, int flame) {

}

void CHARA_OBJECT::MoveToAngleDeg(double deg, double speed) {

}

void CHARA_OBJECT::MoveToAngleDeg(double deg, int flame) {

}

//speed/F�̑��x��dig(�����v��肪��)������]
void CHARA_OBJECT::MoveAngleRad(double rad, double speed) {

}

void CHARA_OBJECT::MoveAngleRad(double rad, int flame) {

}

void CHARA_OBJECT::MoveToAngleRad(double rad, double speed) {

}

void CHARA_OBJECT::MoveToAngleRad(double rad, int flame) {

}

//Player�̍��W���擾
POINT2D CHARA_OBJECT::GetPlayerPos() {
	return common->player->data->pos;
}

//position�̍��W�Ƀ��[�v
void CHARA_OBJECT::Warp(const POINT2D &position) {
	data->ChangePos(position);
}

//Player��speed/F�Œǔ�
void CHARA_OBJECT::HomingToPlayer(double speed) {

}

void CHARA_OBJECT::TurnToPlayer(double homing) {

	VEC2D a, b;
	a = GetPlayerPos() - data->pos;
	b = AngleToVector(data->angle);

	if (a.cross(b) > 0.0) {
		data->angle += homing;
	}
	else {
		data->angle -= homing;
	}

	rad_zero(&data->angle);

}

//���ł���
void CHARA_OBJECT::Disappering() {
	mgrp->RemoveChara(itr);
}

//�G�t�F�N�g�ݒ�
void CHARA_OBJECT::SetStatusEffect(StatusEffect effect, int flag) {

}

//enemy������
void CHARA_OBJECT::SummonEnemy(int type) {

	//CHARA_OBJECT *datam = NULL;

	//mgrp->GetDefaultEnemy(datam, type);
	//mgrp->AddChara(datam);

}

void CHARA_OBJECT::SummonEnemy(CHARA_OBJECT *enemydata) {
	mgrp->AddChara(enemydata);
}

//bullet������
void CHARA_OBJECT::SummonBullet() {

}

VEC2D CHARA_OBJECT::AngleToVector(double angle) {

	double movex, movey;
	movex = cos(angle);
	movey = -1*sin(angle);

	return VEC2D(movex, movey);

}

void CHARA_OBJECT::ChangeHitObject(double r) {

	this->hit->ChangeHit(r);

}

void CHARA_OBJECT::FaceForPlayer() {

	double r, angle;
	ConvertForAngleRadius(&VEC2D(GetPlayerPos() - data->pos), &r, &angle);
	data->ChangeAngle(angle);

}

void CHARA_OBJECT::Effect(EffectType type, POINT2D *pos) {

	EFFECT_OBJECT *newef = new EFFECT_OBJECT(type, 0, common, pos);
	common->effect->AddEffect(newef);

}

void CHARA_OBJECT::EffectWith(EffectType type, CHARA_HIT *hit) {

	Effect(type, &hit->CalcMiddlePoint(hit));

}