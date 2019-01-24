#include <vector>
#include <math.h>
#include <typeinfo>
#include "DxLib.h"
#include "SceneMGR.h"
#include "game.h"
#include "hit.h"

//コリジョンモジュール
HIT_OBJMGR::HIT_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	common->hit = this;
	CharaHit = new std::list<CHARA_HIT*>;
	ResetList_CharaHit = new std::list<int>;
	WallHit = new std::list<WALL_HIT*>;
	ResetList_WallHit = new std::list<int>;

}

void HIT_OBJMGR::Update() {

	ResetElement();

}


void HIT_OBJMGR::ResetElement() {

	//削除リストresetに入っているデータを一括削除
	if (ResetList_CharaHit->empty() == false) {

		ResetList_CharaHit->sort();
		auto itr_reset = ResetList_CharaHit->begin();
		int i = 0;

		for (auto itr = CharaHit->begin(); itr != CharaHit->end();) {
			if (*itr_reset == i) {
				itr = CharaHit->erase(itr);
				itr_reset++;
				if (itr_reset == ResetList_CharaHit->end()) break;
			}
			else {
				++itr;
			}
			i++;
		}
		ResetList_CharaHit->clear();
	}

	if (ResetList_WallHit->empty() == false) {

		ResetList_WallHit->sort();
		auto itr_reset = ResetList_WallHit->begin();
		int i = 0;

		for (auto itr = WallHit->begin(); itr != WallHit->end();) {
			if (*itr_reset == i) {
				itr = WallHit->erase(itr);
				itr_reset++;
				if (itr_reset == ResetList_WallHit->end()) break;
			}
			else {
				++itr;
			}
			i++;
		}
		ResetList_WallHit->clear();
	}

}

void HIT_OBJMGR::Add(CHARA_HIT *charahit) {

	CharaHit->push_back(charahit);
	charahit->GetItrnum(CharaHit->size());
	charahit->GetMgr(this);

}

void HIT_OBJMGR::Add(WALL_HIT *wallhit) {

	WallHit->push_back(wallhit);
	wallhit->GetItrnum(WallHit->size());
	wallhit->GetMgr(this);

}

void HIT_OBJMGR::RemoveChara(int itrnum) {

	ResetList_CharaHit->push_back(itrnum);

}

void HIT_OBJMGR::RemoveWall(int itrnum) {

	ResetList_WallHit->push_back(itrnum);

}


double HIT_OBJECT::CalcSegmentDist(POINT2D *sp1, VEC2D *sv1, POINT2D *s2) {

	VEC2D a = *s2 - *sp1;
	VEC2D b = *s2 - (*sp1 + *sv1);

	if (sv1->dot(a) * sv1->dot(b) >= 0) {
		//線分の外
		if (a.lengthSq() < b.lengthSq())	return a.length();
		else								return b.length();

	}
	else {

		return fabs(sv1->GetNormal().cross(a));

	}

}

//■■■■■■■■■■■■CHARA_HIT■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//---------------------------------------------------------------------------
//円：引数なしのイニシャライザ
//---------------------------------------------------------------------------
CHARA_HIT::CHARA_HIT(Member m, bool isWall){
	member = m;
	isCheckWall = isWall;
	isHitWall = false;
}

//---------------------------------------------------------------------------
//円：中心点と半径指定のイニシャライザ
//---------------------------------------------------------------------------
CHARA_HIT::CHARA_HIT(POINT2D *mid, double r, Member m, bool isWall){

	middle = *mid;
	radius = r;
	member = m;
	isCheckWall = isWall;
	
}

//---------------------------------------------------------------------------
//円：中心点と半径指定のイニシャライザ
//---------------------------------------------------------------------------
CHARA_HIT::CHARA_HIT(POINT2D *mid, POINT2D *a, Member m, bool isWall){

	middle = *mid;
	radius = (*a - *mid).length();
	member = m;
	isCheckWall = isWall;

}

//---------------------------------------------------------------------------
//円：円形との衝突判定
//---------------------------------------------------------------------------
bool CHARA_HIT::HitCheck(CHARA_HIT *obj) {

	DIM2D dif;

	dif = this->middle - obj->middle;
	return ( dif.length() + EPS < (this->radius + obj->radius) );	//衝突していなければ0、衝突していれば0以外を返す（衝突しているときの条件を書く）

}

bool CHARA_HIT::HitCheck(WALL_HIT *obj) {
	
	float d;	//距離d = (S×A) / |S|
	VEC2D a, b;	//線分の始点から円の中心点まで向かうベクトル

	a = middle - obj->start;
	b = middle - (obj->start + obj->Dvector);

	if (obj->Dvector.dot(a) * obj->Dvector.dot(b) - EPS <= 0.0f) {

		d = fabs(obj->Dvector.cross(a)) / fabs(obj->Dvector.length());

		if ((d + EPS) < radius) {
			return 1;
		}
		else {
			return 0;
		}

	}
	else if ((a.length() + EPS) < radius || (b.length() + EPS) < radius) {
		return 1;
	}
	else {
		return 0;
	}

}

CHARA_HIT* CHARA_HIT::ParallelMove(VEC2D *v) {

	CHARA_HIT *newobj;
	newobj = new CHARA_HIT(&POINT2D(middle + *v), radius, member, isCheckWall);
	return newobj;

}

CHARA_MOVEHIT* CHARA_HIT::MoveObject(VEC2D *v) {

	CHARA_MOVEHIT *newobj;
	newobj = new CHARA_MOVEHIT(&middle, v, radius);

	return newobj;

}

VEC2D CHARA_HIT::CalcPushVec(WALL_HIT *wall, CHARA_MOVEHIT *movehit) {
	
	if (movehit->HitCheck(wall) == 0) {
		return VEC2D(0, 0);		
	}

	VEC2D a, c, d, e;
	float b;

	a = middle - wall->start;
	c = wall->Dvector.GetNormal();
	b = c.cross(a);
	d = VEC2D(c.y, -c.x);

	e = VEC2D(d.x * (b + radius), d.y * (b + radius));
	return e;
	
}

#define MAX_WALLCHECK_COUNT 4
void CHARA_HIT::WallPush(VEC2D *move){

	int ic = 0;
	std::list<WALL_HIT*> hitting;
	double walldis;
	double a;
	WALL_HIT *nearwall = NULL;
	CHARA_HIT *movingobj;
	VEC2D push;
	isHitWall = false;

	//判定は最大4回まで
	while (ic < MAX_WALLCHECK_COUNT) {

		hitting.clear();
		walldis = 32767;
		a = 0;
		nearwall = NULL;

		moveobj = MoveObject(move);

		for (auto itr = mgr->WallHit->begin(); itr != mgr->WallHit->end(); itr++) {
			if ( moveobj->HitCheck(*itr) == true ) {	//衝突しているならば
				hitting.push_back((*itr));	//hittingに登録
			}
		}
		//もし一つも接触している壁がなければ脱出
		if (hitting.size() == 0)	break;

		//移動前の図形と最も最短距離が近い壁を見つけ出す
		for (auto itr = hitting.begin(); itr != hitting.end(); itr++) {

			a = CalcNearDistanceToSegment(*itr);

			if (a < walldis || nearwall == NULL) {
				walldis = a;
				nearwall = (*itr);
			}

		}

		//移動後の物体を仮想的に作成
		movingobj = ParallelMove(move);

		//最も距離が近い壁との押し出しベクトルを計算、moveに代入
		push = movingobj->CalcPushVec(nearwall, moveobj);
		*move = *move + push;
		
		isHitWall = true;
		ic++;

	}

}

void CHARA_HIT::UpdateMoveObj(VEC2D *move) {

	if (isCheckWall == true) {
		WallPush(move);
	}

	//移動オブジェクトの更新
	moveobj = MoveObject(move);

	//離散的オブジェクトの更新
	middle = middle + *move;

}

bool CHARA_HIT::HitCheckOnMove(CHARA_HIT *obj) {

	if (!obj->moveobj) return false;
	return moveobj->HitCheck(obj->moveobj);

}

double CHARA_HIT::CalcDistance(POINT2D *p) {
	//円の中心点とpとの距離を返す
	double a = (this->middle - *p).length();
	return a;

}

double CHARA_HIT::CalcDistance(CHARA_HIT *obj) {

	//円同士の最短距離を返す　重なっているとマイナスになる
	return CalcDistance(&obj->middle) - (this->radius + obj->radius);

}

double CHARA_HIT::CalcNearDistanceToSegment(WALL_HIT *obj) {

	return CalcSegmentDist(&obj->start, &obj->Dvector, &middle) - radius;

}

POINT2D CHARA_HIT::CalcMiddlePoint(CHARA_HIT *obj) {

	//中点を返す
	POINT2D a = middle + obj->middle;
	return a / 2.0;

}


//■■■■■■■■■■■■WALL_HIT■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//---------------------------------------------------------------------------
//線分：引数なしのイニシャライザ
//---------------------------------------------------------------------------
WALL_HIT::WALL_HIT(){

}

//---------------------------------------------------------------------------
//線分：始点とベクトル指定のイニシャライザ
//---------------------------------------------------------------------------
WALL_HIT::WALL_HIT(POINT2D *s, VEC2D *v){

	start = *s;
	Dvector = *v;

}

//---------------------------------------------------------------------------
//線分：始点と終点指定のイニシャライザ
//---------------------------------------------------------------------------
WALL_HIT::WALL_HIT(POINT2D *s, POINT2D *e){

	start = *s;
	Dvector = *e - *s;

}



//■■■■■■■■■■■■CHARA_MOVEHIT■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

//---------------------------------------------------------------------------
//線分：引数なしのイニシャライザ
//---------------------------------------------------------------------------
CHARA_MOVEHIT::CHARA_MOVEHIT(){

}

CHARA_MOVEHIT::CHARA_MOVEHIT(POINT2D *s, VEC2D *v, double r){

	start = *s;
	Dvector = *v;
	radius = r;

}

//---------------------------------------------------------------------------
//線分：線分ベクトルとの衝突判定
//---------------------------------------------------------------------------
bool CHARA_MOVEHIT::HitCheck(WALL_HIT *obj) {
	
	float t1, t2;
	VEC2D s;

	s = start - obj->start;
	t1 = s.cross(obj->Dvector) / obj->Dvector.cross(Dvector);
	t2 = s.cross(Dvector) / obj->Dvector.cross(Dvector);

	//もし線分同士が交差しているのならば、衝突している
	if (0.0f - EPS <= t1 && t1 - EPS <= 1.0f && 0.0f - EPS <= t2 && t2 - EPS <= 1.0f) return true;
	
	//内積の積がマイナスならば
	//外積 < 半径　ならば return 1

	//内積の積がプラスならば
	//点同士の距離 < 半径　ならば return 1

	if (CalcSegmentDist(&start, &Dvector, &obj->start) + EPS < radius) {
		return true;
	}
	if (CalcSegmentDist(&start, &Dvector, &VEC2D(obj->start + obj->Dvector)) + EPS < radius) {
		return true;
	}
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &start) + EPS < radius) {
		return true;
	}
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &VEC2D(start + Dvector)) + EPS < radius) {
		return true;
	}

	return false;

}

//---------------------------------------------------------------------------
//線分：線分ベクトルとの衝突判定
//---------------------------------------------------------------------------
bool CHARA_MOVEHIT::HitCheck(CHARA_MOVEHIT *obj) {

	float t1, t2;
	VEC2D s;

	s = start - obj->start;
	t1 = s.cross(obj->Dvector) / obj->Dvector.cross(Dvector);
	t2 = s.cross(Dvector) / obj->Dvector.cross(Dvector);

	//もし線分同士が交差しているのならば、衝突している
	if (0.0f - EPS <= t1 && t1 - EPS <= 1.0f && 0.0f - EPS <= t2 && t2 - EPS <= 1.0f) return true;

	//内積の積がマイナスならば
	//外積 < 半径　ならば return 1

	//内積の積がプラスならば
	//点同士の距離 < 半径　ならば return 1

	if (CalcSegmentDist(&start, &Dvector, &obj->start) + EPS < radius + obj->radius) {
		return true;
	}
	if (CalcSegmentDist(&start, &Dvector, &VEC2D(obj->start + obj->Dvector)) + EPS < radius + obj->radius) {
		return true;
	}
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &start) + EPS < radius + obj->radius) {
		return true;
	}
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &VEC2D(start + Dvector)) + EPS < radius + obj->radius) {
		return true;
	}

	return false;

/*
	float t1, t2;
	VEC2D s;

	s = start - obj->start;
	t1 = s.cross(Dvector) / Dvector.cross(obj->Dvector);
	t2 = s.cross(obj->Dvector) / Dvector.cross(obj->Dvector);

	//もし線分同士が交差しているのならば、衝突している
	if (0.0f - EPS <= t1 && t1 - EPS <= 1.0f && 0.0f - EPS <= t2 && t2 - EPS <= 1.0f) return 1;

	//内積の積がマイナスならば
	//外積 < 半径　ならば return 1

	//内積の積がプラスならば
	//点同士の距離 < 半径　ならば return 1

	if (CalcSegmentDist(&start, &Dvector, &obj->start) - EPS < radius) return true;
	if (CalcSegmentDist(&start, &Dvector, &VEC2D(obj->start + obj->Dvector)) - EPS < radius) return true;
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &start) - EPS < radius) return true;
	if (CalcSegmentDist(&obj->start, &obj->Dvector, &VEC2D(start + Dvector)) - EPS < radius) return true;

	return 0;
*/
}

//---------------------------------------
// その他
//---------------------------------------

POINT2D ConvertForPoint2(double r, double angle) {

	double movex, movey;
	movex = r * cos(angle);
	movey = -1 * r * sin(angle);

	return POINT2D(movex, movey);

}

VEC2D ConvertForVector2(double r, double angle) {

	double movex, movey;
	movex = r * cos(angle);
	movey = -1 * r * sin(angle);

	return VEC2D(movex, movey);

}

void ConvertForAngleRadius(POINT2D *vec, double *r, double *angle) {

	*r = vec->length();
	double sinvec, cosvec, sinval, cosval;

	sinvec = -1 * vec->y / *r;
	cosvec = vec->x / *r;
	cosval = acos(cosvec);	//0..pi
	sinval = asin(sinvec);  //-pi/2..pi/2

	if (cosval <= (pi() / 2)) {
		if (sinval >= 0) *angle = sinval; //第1象限
		else *angle = 2 * pi() + sinval; //第4象限
	}
	else {
		if (sinval >= 0) *angle = cosval; //第2象限
		else *angle = 2 * pi() - cosval; //第3象限
	}

	rad_zero(angle);

}

POINT2D Absoluter(double r, double angle, POINT2D *o, double oangle) {

	// oを基準に、r+angleの絶対座標を返す
	return *o + ConvertForVector2(r, oangle+angle);

}

POINT2D Absoluter(POINT2D *vec, POINT2D *o, double oangle) {

	double r, angle;
	ConvertForAngleRadius(vec, &r, &angle);
	return Absoluter(r, angle, o, oangle);

}

POINT2D AbsoluterAngle(double angle, double oangle) {

	return ConvertForVector2(1, oangle + angle);

}

POINT2D AbsoluterAngle(double angle, POINT2D *oangle) {

	return POINT2D(0, 0);

}

// 2018/08/15
// GetAllCollisionList, GetCollisionListから作り始める
