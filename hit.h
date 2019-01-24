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
// 2次ベクトルクラス
//-------------------------------------------------------------
class DIM2D {

public:
	double x;
	double y;

	DIM2D() {};		//コンストラクタ
	DIM2D(double x, double y) { this->x = x, this->y = y; };	//イニシャライザ
	~DIM2D() {};	//デストラクタ
	DIM2D operator +(const DIM2D &vec) const { return DIM2D( this->x + vec.x, this->y + vec.y ); };	//加算演算子
	DIM2D operator -(const DIM2D &vec) const { return DIM2D( this->x - vec.x, this->y - vec.y ); };	//減算演算子
	DIM2D operator -() const { return DIM2D( -1 * this->x, -1 * this->y ); };	//負の数
	DIM2D operator *(const DIM2D &vec) const { return DIM2D( this->x * vec.x, this->y * vec.y ); };	//2D乗算演算子
	DIM2D operator /(const DIM2D &vec) const { return DIM2D( this->x / vec.x, this->y / vec.y ); };	//2D除算演算子
	DIM2D operator *(double a) const { return DIM2D( this->x * a, this->y * a ); };	//スカラー乗算演算子
	DIM2D operator /(double a) const { return DIM2D( this->x / a, this->y / a ); };	//スカラー除算演算子
	double dot(const DIM2D &vec) const { return ( this->x * vec.x + this->y * vec.y ); };	//内積
	double cross(const DIM2D &vec) const { return ( this->x * vec.y - this->y * vec.x ); };	//外積
	double lengthSq() const { return ( this->x * this->x + this->y * this->y ); };	//ベクトルの大きさの2乗
	double length() const { return sqrt( lengthSq() ); };	//ベクトルの大きさ
	void normal() { const double len = length(); if (len > 0.0f) { this->x /= len; this->y /= len; } };	//ベクトルの正規化(単位ベクトル)
	DIM2D GetNormal() { const double len = length(); if (len > 0.0f) { return DIM2D(this->x / len, this->y / len); } return DIM2D(0.0f, 0.0f); };	//正規化したベクトルの取得

};

//-------------------------------------------------------------
// 2次元位置ベクトルクラス
//-------------------------------------------------------------
typedef DIM2D POINT2D;

//-------------------------------------------------------------
// 2次元方向ベクトルクラス
//-------------------------------------------------------------
class VEC2D :public DIM2D {

public:
	VEC2D() {};
	VEC2D(double x, double y) : DIM2D(x, y){};	//イニシャライザ
	VEC2D(const DIM2D &vec) : DIM2D(vec){};
	~VEC2D() {};
	VEC2D &operator=(const DIM2D &vec) { x = vec.x; y = vec.y; return *this; };
	bool isVertical(const VEC2D &vec) const { double d = dot(vec); return (-EPS < d && d < EPS); } 	// 垂直関係にある？ 
	bool isParallel(const VEC2D &vec) const { double d = cross(vec); return (-EPS < d && d < EPS); } // 平行関係にある？ 
	bool isSharpAngle(const VEC2D &vec) const { return (dot(vec) >= 0.0f); } 						// 鋭角関係？ 

};

//クラスの前方参照
class CHARA_HIT;
class WALL_HIT;
class CHARA_MOVEHIT;
class HIT_OBJMGR;
class COMMON_DATA;
class BASE_OBJMGR;
class BASE_OBJECT;


//-------------------------------------------------------------
// 物理衝突オブジェクトの基底クラス
//-------------------------------------------------------------
class HIT_OBJECT : public BASE_OBJECT{

public:
	HIT_OBJMGR *mgr;
	int itrnum;
	void GetMgr(HIT_OBJMGR *mgr) { this->mgr = mgr; }
	void GetItrnum(int itrnum) { this->itrnum = itrnum; };

	HIT_OBJECT() {};			//コンストラクタ
	virtual ~HIT_OBJECT() {};	//デストラクタ
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
// 形状の種類：円
//-------------------------------------------------------------
class CHARA_HIT :public HIT_OBJECT{

public:
	POINT2D middle; //中心座標
	double radius; //半径
	VEC2D move;
	CHARA_MOVEHIT *moveobj;
	Member member;
	bool isCheckWall;	//trueならば壁判定を行う
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
// 形状の種類：線分ベクトル
//-------------------------------------------------------------
class WALL_HIT :public HIT_OBJECT {

public:
	POINT2D start; //始点
	VEC2D Dvector; //方向ベクトル

	WALL_HIT();
	WALL_HIT(POINT2D *s, VEC2D *v);
	WALL_HIT(POINT2D *s, POINT2D *e);
	~WALL_HIT() {};

	void RemoveForList() { mgr->RemoveWall(itrnum); };

};


//-------------------------------------------------------------
// 形状の種類：カプセル
//-------------------------------------------------------------
class CHARA_MOVEHIT :public HIT_OBJECT {

public:
	POINT2D start; //始点
	VEC2D Dvector; //方向ベクトル
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

Absoluter  使い方

第1引数		相対位置(X:前, Y:左手方向)
第2引数		基準となる座標
第3引数		基準となる角度(0度)









*/