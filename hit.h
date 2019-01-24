#pragma once

#include <vector>
#include <list>
#include <cmath>

#include "game.h"
#include "gclass.h"

enum Member {

	Player_hit,
	Enemy_hit,
	Boss_hit,
	Bullet_hit,
	Item_hit,
	Virtual_hit

};


//-------------------------------------------------------------
// 2���x�N�g���N���X
//-------------------------------------------------------------
class DIM2D {

public:
	double x;
	double y;

	DIM2D() {};		//�R���X�g���N�^
	DIM2D(double x, double y) { this->x = x, this->y = y; };	//�C�j�V�����C�U
	~DIM2D() {};	//�f�X�g���N�^
	DIM2D operator +(const DIM2D &vec) const { return DIM2D( this->x + vec.x, this->y + vec.y ); };	//���Z���Z�q
	DIM2D operator -(const DIM2D &vec) const { return DIM2D( this->x - vec.x, this->y - vec.y ); };	//���Z���Z�q
	DIM2D operator -() const { return DIM2D( -1 * this->x, -1 * this->y ); };	//���̐�
	DIM2D operator *(const DIM2D &vec) const { return DIM2D( this->x * vec.x, this->y * vec.y ); };	//2D��Z���Z�q
	DIM2D operator /(const DIM2D &vec) const { return DIM2D( this->x / vec.x, this->y / vec.y ); };	//2D���Z���Z�q
	DIM2D operator *(double a) const { return DIM2D( this->x * a, this->y * a ); };	//�X�J���[��Z���Z�q
	DIM2D operator /(double a) const { return DIM2D( this->x / a, this->y / a ); };	//�X�J���[���Z���Z�q
	double dot(const DIM2D &vec) const { return ( this->x * vec.x + this->y * vec.y ); };	//����
	double cross(const DIM2D &vec) const { return ( this->x * vec.y - this->y * vec.x ); };	//�O��
	double lengthSq() const { return ( this->x * this->x + this->y * this->y ); };	//�x�N�g���̑傫����2��
	double length() const { return sqrt( lengthSq() ); };	//�x�N�g���̑傫��
	void normal() { const double len = length(); if (len > 0.0f) { this->x /= len; this->y /= len; } };	//�x�N�g���̐��K��(�P�ʃx�N�g��)
	DIM2D GetNormal() { const double len = length(); if (len > 0.0f) { return DIM2D(this->x / len, this->y / len); } return DIM2D(0.0f, 0.0f); };	//���K�������x�N�g���̎擾

};

//-------------------------------------------------------------
// 2�����ʒu�x�N�g���N���X
//-------------------------------------------------------------
typedef DIM2D POINT2D;

//-------------------------------------------------------------
// 2���������x�N�g���N���X
//-------------------------------------------------------------
class VEC2D :public DIM2D {

public:
	VEC2D() {};
	VEC2D(double x, double y) : DIM2D(x, y){};	//�C�j�V�����C�U
	VEC2D(const DIM2D &vec) : DIM2D(vec){};
	~VEC2D() {};
	VEC2D &operator=(const DIM2D &vec) { x = vec.x; y = vec.y; return *this; };
	bool isVertical(const VEC2D &vec) const { double d = dot(vec); return (-EPS < d && d < EPS); } 	// �����֌W�ɂ���H 
	bool isParallel(const VEC2D &vec) const { double d = cross(vec); return (-EPS < d && d < EPS); } // ���s�֌W�ɂ���H 
	bool isSharpAngle(const VEC2D &vec) const { return (dot(vec) >= 0.0f); } 						// �s�p�֌W�H 

};

//�N���X�̑O���Q��
class CHARA_HIT;
class WALL_HIT;
class CHARA_MOVEHIT;
class HIT_OBJMGR;
class COMMON_DATA;
class BASE_OBJMGR;
class BASE_OBJECT;


//-------------------------------------------------------------
// �����Փ˃I�u�W�F�N�g�̊��N���X
//-------------------------------------------------------------
class HIT_OBJECT : public BASE_OBJECT{

public:
	HIT_OBJMGR *mgr;
	int itrnum;
	void GetMgr(HIT_OBJMGR *mgr) { this->mgr = mgr; }
	void GetItrnum(int itrnum) { this->itrnum = itrnum; };

	HIT_OBJECT() {};			//�R���X�g���N�^
	virtual ~HIT_OBJECT() {};	//�f�X�g���N�^
	virtual void RemoveForList() = 0;
	double CalcSegmentDist(POINT2D *sp1, VEC2D *sv1, POINT2D *s2);

	void Initialize() {};
	void Finalize() {};
	void Update() {};
	void Draw() {};

};

class HIT_OBJMGR : public BASE_OBJMGR {

public:

	std::list<CHARA_HIT*> *CharaHit;
	std::list<int> *ResetList_CharaHit;
	std::list<WALL_HIT*> *WallHit;
	std::list<int> *ResetList_WallHit;

	HIT_OBJMGR(COMMON_DATA *common);

	void Initialize() {};
	void Finalize() {};
	void Update();
	void Draw() {};

	void Add(CHARA_HIT *charahit);
	void Add(WALL_HIT *wallhit);
	void RemoveChara(int itrnum);
	void RemoveWall(int itrnum);

protected:
	void ResetElement();

};

//-------------------------------------------------------------
// �`��̎�ށF�~
//-------------------------------------------------------------
class CHARA_HIT :public HIT_OBJECT{

public:
	POINT2D middle; //���S���W
	double radius; //���a
	VEC2D move;
	CHARA_MOVEHIT *moveobj;
	Member member;
	bool isCheckWall;	//true�Ȃ�Εǔ�����s��
	bool isHitWall;

	CHARA_HIT(Member m, bool isWall);
	CHARA_HIT(POINT2D *mid, double r, Member m, bool isWall);
	CHARA_HIT(POINT2D *mid, POINT2D *a, Member m, bool isWall);
	~CHARA_HIT() {};

	void WallPush(VEC2D *move);
	VEC2D CalcPushVec(WALL_HIT *wall, CHARA_MOVEHIT *movehit);
	bool HitCheck(CHARA_HIT *obj);
	bool HitCheck(WALL_HIT *obj);
	bool HitCheckOnMove(CHARA_HIT *obj);
	void UpdateMoveObj(VEC2D *move);
	
	CHARA_HIT *ParallelMove(VEC2D *v);
	CHARA_MOVEHIT* MoveObject(VEC2D *v);
	double CalcNearDistanceToSegment(WALL_HIT *obj);
	double CalcDistance(POINT2D *p);
	double CalcDistance(CHARA_HIT *obj);
	POINT2D CalcMiddlePoint(CHARA_HIT *obj);

	void RemoveForList() { mgr->RemoveChara(itrnum); };
	void ChangeHit(double r) { radius = r; };

};


//-------------------------------------------------------------
// �`��̎�ށF�����x�N�g��
//-------------------------------------------------------------
class WALL_HIT :public HIT_OBJECT {

public:
	POINT2D start; //�n�_
	VEC2D Dvector; //�����x�N�g��

	WALL_HIT();
	WALL_HIT(POINT2D *s, VEC2D *v);
	WALL_HIT(POINT2D *s, POINT2D *e);
	~WALL_HIT() {};

	void RemoveForList() { mgr->RemoveWall(itrnum); };

};


//-------------------------------------------------------------
// �`��̎�ށF�J�v�Z��
//-------------------------------------------------------------
class CHARA_MOVEHIT :public HIT_OBJECT {

public:
	POINT2D start; //�n�_
	VEC2D Dvector; //�����x�N�g��
	double radius;

	CHARA_MOVEHIT();
	CHARA_MOVEHIT(POINT2D *s, VEC2D *v, double r);
	~CHARA_MOVEHIT() {};

	bool HitCheck(CHARA_MOVEHIT *obj);
	bool HitCheck(WALL_HIT *obj);

	void RemoveForList() {}

};

POINT2D ConvertForPoint2(double r, double angle);
VEC2D ConvertForVector2(double r, double angle);
void ConvertForAngleRadius(POINT2D *vec, double *r, double *angle);
POINT2D Absoluter(POINT2D *vec, POINT2D *o, double oangle);
POINT2D Absoluter(double r, double angle, POINT2D *o, double oangle);
POINT2D AbsoluterAngle(double angle, double oangle);
POINT2D AbsoluterAngle(double angle, POINT2D *oangle);

/*

Absoluter  �g����

��1����		���Έʒu(X:�O, Y:�������)
��2����		��ƂȂ���W
��3����		��ƂȂ�p�x(0�x)









*/