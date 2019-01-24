#pragma once
#include <vector>
#include <list>
#include <string>

#include "gclass.h"
#include "hit.h"
#include "camera.h"
#include "effect.h"

class COMMON_DATA;
class CHARA_DEFINFO;
class ENEMY_BASE;
class HIT_OBJECT;
class CHARA_OBJECT;
class MAP_OBJECT;

enum CharaMember {

	None_mem,
	Player_mem,
	Enemy_mem,
	Boss_mem,
	Bullet_mem,
	Virtual_mem

};

enum CharaType {

	None,
	Player,
	Sword_of_Player,
	GrayKnight,
	Sword_of_GrayKnight,
	CoronaMage,
	Sword_of_CoronaMage,
	Wave_of_CoronaMage,
	Meteor_of_CoronaMage,
	Explosion_of_meteor,
	Shadow_of_meteor,
	LateSniper,
	Bullet_of_LateSniper

};

enum StatusEffect {

	Invisible,
	Paralysis,
	StrengthProduct,
	DeffenceProduct,
	SpeedProduct,
	KnockBackResChange

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラのマネージャークラス
//---------------------------------------------------------------------------
class CHARA_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	std::list<CHARA_OBJECT*> *chara;
	std::list<int> *reset;
	std::vector<int> *GrHandle;
	int CountEnemy;
	int stage;
	int PlayerHP;

	CHARA_OBJECT *boss = NULL;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	CHARA_OBJMGR(COMMON_DATA *common, int stage, int PlayerHP);	//コンストラクタ

	void InitGr();
	int GetGrHandle(int num) { return GrHandle->at(num); };
	void SetStageChara();
	void AddChara(CHARA_OBJECT *charadata);	//敵を追加する
	void RemoveChara(int itrnum);	//敵を削除する
	void EnemyCount();
	void GetBoss(CHARA_OBJECT *b) { boss = b; }

	CHARA_HIT* GetDefaultCharaHit(POINT2D init_pos, CharaType type);
	CHARA_DEFINFO* GetDefaultCharaData(POINT2D init_pos, double init_angle, CharaType type);

private:
	void PlayerInit();
	void ResetListElement();

};

//---------------------------------------------------------------------------
//ゲームオブジェクト：キャラ（抽象クラス）
//---------------------------------------------------------------------------
class CHARA_OBJECT : public BASE_OBJECT{

public:

	//■■■メンバ変数■■■
	CHARA_HIT *hit;	//衝突判定オブジェクトのデータ
	CHARA_DEFINFO *data;
	int itr;
	CHARA_OBJMGR *mgrp;
	bool isDraw;

	int DamageSound;
	int KillSound;

	//■■■メンバ関数■■■
	virtual void Initialize();
	virtual void Finalize();
	virtual void Update();		//更新処理
	virtual void Think();
	virtual void Collision();
	virtual void Draw();		//描画処理
	void DrawDeath();
	void InputItr(int itrnum);
	void InputMgr(CHARA_OBJMGR *mgrpointer);
	void WallCheck();
	void MoveKnockBack();
	int IgnoreDefDamage(double value, bool isignoretime);
	int Damage(double value, bool isignoretime);
	int Damage(double motion, double strength, bool isignoretime);
	void KnockBack(VEC2D *m);
	void Kill();
	CHARA_OBJECT(CHARA_HIT *hitdata, CHARA_DEFINFO *data, COMMON_DATA *common);		//コンストラクタ
	virtual ~CHARA_OBJECT();	//デストラクタ




protected:

	void MoveStraight(double speed);	//現在向いている方向にspeedの速度で進む

	void MoveStr(VEC2D *direction);	//directionの方向に移動
	void MoveStrTo(POINT2D *position); //positionの場所に移動
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

	POINT2D GetPlayerPos();				//Playerの座標を取得
	void Warp(const POINT2D &position);					//positionの座標にワープ
	void HomingToPlayer(double speed);		//Playerをspeed/Fで追尾
	void TurnToPlayer(double homing);	//homingの速度でPlayerに旋回
	void Disappering();			//消滅する
	void SetStatusEffect(StatusEffect effect, int flag);

	void SummonEnemy(int type);			//enemyを召喚
	void SummonEnemy(CHARA_OBJECT *enemydata);

	void SummonBullet();		//bulletを召喚
	VEC2D AngleToVector(double angle);
	void ChangeHitObject(double r);
	void FaceForPlayer();

	void Effect(EffectType type, POINT2D *pos);
	void EffectWith(EffectType type, CHARA_HIT *hit);

};



class CHARA_DEFINFO {

public:
	POINT2D pos;
	VEC2D move;
	double angle;
	int timer;
	int islive;
	bool iscount;
	int health;
	double strength;
	double deffence;
	double speed;
	double knockback_res;
	int flag;
	CharaType charatype;
	CharaMember charamem;
	std::string charaname;

	int MaxHP;
	int IgnoreDamageCT;

	int GrHandle;
	int deathcount;
	bool isDeathSmoke;

	double KnockBackTime;
	VEC2D KnockBack;
	double DamageIgnoreTime;

	CHARA_DEFINFO(
		POINT2D *pos,
		VEC2D *move,
		double angle,
		int timer,
		int islive,
		bool iscount,
		int health,
		double strength,
		double deffence,
		double speed,
		double knockback_res,
		int flag,
		CharaType charatype,
		CharaMember charamem,
		std::string charaname,
		int IgDmgCt
	);

	void ChangePos(POINT2D data) { pos = data; };
	void ChangeMove(VEC2D data) { move = data; };
	void ChangeAngle(double data) { angle = data; };

};