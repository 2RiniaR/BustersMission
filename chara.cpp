#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "hit.h"
#include "move.h"
#include "map.h"
#include "enemy.h"
#include "chara.h"


using namespace std;

//---------------------------------------------------------------------------
//CHARA_OBJMGR：コンストラクタ
//---------------------------------------------------------------------------
CHARA_OBJMGR::CHARA_OBJMGR(COMMON_DATA *common, int stage, int PlayerHP) {

	this->common = common;
	common->chara = this;
	chara = new std::list<CHARA_OBJECT*>;
	reset = new std::list<int>;
	GrHandle = new std::vector<int>;
	CountEnemy = 0;
	this->stage = stage;
	this->PlayerHP = PlayerHP;

}

//---------------------------------------------------------------------------
//CHARA_OBJMGR：初期処理
//---------------------------------------------------------------------------
void CHARA_OBJMGR::Initialize(){

	InitGr();
	PlayerInit();
	SetStageChara();

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			(*itr)->Initialize();
			
		}
	}


}

//---------------------------------------------------------------------------
//CHARA_OBJMGR：終了処理
//---------------------------------------------------------------------------
void CHARA_OBJMGR::Finalize() {

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			(*itr)->Finalize();
		}
	}

}

//---------------------------------------------------------------------------
//CHARA_OBJMGR：更新処理
//---------------------------------------------------------------------------
void CHARA_OBJMGR::Update() {

	int i = 0;

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->Update();
			i++;
		}
	}

	//削除リストresetに入っているキャラデータを一括削除
	ResetListElement();

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->WallCheck();
			i++;
		}
	}

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->Collision();
			i++;
		}
	}

	EnemyCount();

}


//---------------------------------------------------------------------------
//CHARA_OBJMGR：描画処理
//---------------------------------------------------------------------------
void CHARA_OBJMGR::Draw() {

	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			if((*itr)->data->deathcount == 0) (*itr)->Draw();
			else (*itr)->DrawDeath();
		}
	}

}

//---------------------------------------------------------------------------
//CHARA_OBJMGR：敵を追加する
//---------------------------------------------------------------------------
void CHARA_OBJMGR::AddChara(CHARA_OBJECT *charadata) {

	chara->push_back(charadata);
	charadata->InputItr(chara->size());
	charadata->InputMgr(this);	
	charadata->data->islive = true;
	charadata->data->flag = true;
	charadata->data->MaxHP = charadata->data->health;
	common->hit->Add(charadata->hit);

}

//---------------------------------------------------------------------------
//CHARA_OBJMGR：敵を削除する
//---------------------------------------------------------------------------
void CHARA_OBJMGR::RemoveChara(int itrnum) {

	reset->push_back(itrnum);	//削除リストresetに登録

}

void CHARA_OBJMGR::PlayerInit() {

	CHARA_HIT *player_hit;
	CHARA_DEFINFO *player_data;

	if (stage == 1) {
		player_hit = GetDefaultCharaHit(POINT2D(100, 100), Player);
		player_data = GetDefaultCharaData(POINT2D(100, 100), 0.0, Player);
	}
	else if (stage == 2) {
		player_hit = GetDefaultCharaHit(POINT2D(200, 120), Player);
		player_data = GetDefaultCharaData(POINT2D(200, 120), 0.0, Player);
	}
	else {
		player_hit = GetDefaultCharaHit(POINT2D(600, 600), Player);
		player_data = GetDefaultCharaData(POINT2D(600, 600), 0.0, Player);
	}

	PLAYER_OBJECT *player = new PLAYER_OBJECT(player_hit, player_data, common);

	AddChara(player);

}

void CHARA_OBJMGR::ResetListElement() {

	//削除リストresetに入っているキャラデータを一括削除
	if (reset->empty() == false) {
		reset->sort();
		auto itr_reset = reset->begin();
		int i = 0;

		for (auto itr = chara->begin(); itr != chara->end();) {

			if (*itr_reset == i) {

				(*itr)->hit->RemoveForList();

				if ((*itr) != NULL) {
					if((*itr) != boss) delete (*itr);
					//(*itr) = NULL;
				}

				itr = chara->erase(itr);
				itr_reset++;
				if (itr_reset == reset->end()) break;

			}
			else {
				++itr;
			}
			i++;

		}
		reset->clear();
	}

}

void CHARA_OBJMGR::InitGr() {

	GrHandle->push_back(LoadGraph("data/image/chara/player1.png"));		// 0
	GrHandle->push_back(LoadGraph("data/image/chara/enemy1.png"));		// 1
	GrHandle->push_back(LoadGraph("data/image/chara/enemy4.png"));		// 2
	GrHandle->push_back(LoadGraph("data/image/chara/bullet1.png"));		// 3
	GrHandle->push_back(LoadGraph("data/image/chara/bullet2.png"));		// 4
	GrHandle->push_back(LoadGraph("data/image/chara/bullet3.png"));		// 5
	GrHandle->push_back(LoadGraph("data/image/chara/bullet4.png"));		// 6
	GrHandle->push_back(LoadGraph("data/image/chara/shadow1.png"));		// 7
	GrHandle->push_back(LoadGraph("data/image/chara/death.png"));		// 8
	GrHandle->push_back(LoadGraph("data/image/chara/enemy2.png"));		// 9
	GrHandle->push_back(LoadGraph("data/image/chara/bullet5.png"));		// 10
	GrHandle->push_back(LoadGraph("data/image/other/red.png"));		// 11

}

void CHARA_OBJMGR::EnemyCount() {

	int ct = 0;
	//
	if (chara->empty() == false) {
		for (auto itr = chara->begin(); itr != chara->end(); ++itr) {
			if ((*itr)
				->data->iscount == true) ct++;
		}
	}

	CountEnemy = ct;

}


void CHARA_OBJMGR::SetStageChara() {

	CHARA_HIT* hitm;
	CHARA_DEFINFO *defm;

	if (stage == 1) {

		hitm = GetDefaultCharaHit(POINT2D(250, 250), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(250, 250), 0.0, GrayKnight);
		ENEMY1 *enm1 = new ENEMY1(hitm, defm, common);
		AddChara(enm1);

		hitm = GetDefaultCharaHit(POINT2D(550, 150), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(550, 150), 0.0, GrayKnight);
		ENEMY1 *enm2 = new ENEMY1(hitm, defm, common);
		AddChara(enm2);

		hitm = GetDefaultCharaHit(POINT2D(1000, 610), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(1000, 610), 0.0, GrayKnight);
		ENEMY1 *enm3 = new ENEMY1(hitm, defm, common);
		AddChara(enm3);

		hitm = GetDefaultCharaHit(POINT2D(880, 330), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(880, 330), 0.0, GrayKnight);
		ENEMY1 *enm4 = new ENEMY1(hitm, defm, common);
		AddChara(enm4);

	}
	else if (stage == 2) {

		hitm = GetDefaultCharaHit(POINT2D(700, 150), LateSniper);
		defm = GetDefaultCharaData(POINT2D(700, 150), 0.0, LateSniper);
		ENEMY2 *enm5 = new ENEMY2(hitm, defm, common);
		AddChara(enm5);

		hitm = GetDefaultCharaHit(POINT2D(200, 760), LateSniper);
		defm = GetDefaultCharaData(POINT2D(200, 760), 0.0, LateSniper);
		ENEMY2 *enm6 = new ENEMY2(hitm, defm, common);
		AddChara(enm6);

		hitm = GetDefaultCharaHit(POINT2D(1450, 890), LateSniper);
		defm = GetDefaultCharaData(POINT2D(1450, 890), 0.0, LateSniper);
		ENEMY2 *enm7 = new ENEMY2(hitm, defm, common);
		AddChara(enm7);

		hitm = GetDefaultCharaHit(POINT2D(300, 300), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(300, 300), 0.0, GrayKnight);
		ENEMY1 *enm8 = new ENEMY1(hitm, defm, common);
		AddChara(enm8);

		hitm = GetDefaultCharaHit(POINT2D(910, 770), GrayKnight);
		defm = GetDefaultCharaData(POINT2D(910, 770), 0.0, GrayKnight);
		ENEMY1 *enm9 = new ENEMY1(hitm, defm, common);
		AddChara(enm9);

	}else{

		hitm = GetDefaultCharaHit(POINT2D(600, 250), CoronaMage);
		defm = GetDefaultCharaData(POINT2D(600, 250), 0.0, CoronaMage);
		BOSS1 *enm10 = new BOSS1(hitm, defm, common);
		AddChara(enm10);
		GetBoss(enm10);

	}

}



















//---------------------------------------------------------------------------
//CHARA_OBJECT：イニシャライザ
//---------------------------------------------------------------------------
CHARA_OBJECT::CHARA_OBJECT(CHARA_HIT *hitdata, CHARA_DEFINFO *data, COMMON_DATA *common) {

	this->common = common;
	this->data = data;
	this->hit = hitdata;

	KillSound = LoadSoundMem("data/sound/se/damage6.mp3");
	DamageSound = LoadSoundMem("data/sound/se/damage4.mp3");


}

//---------------------------------------------------------------------------
//CHARA_OBJECT：デストラクタ
//---------------------------------------------------------------------------
CHARA_OBJECT::~CHARA_OBJECT() {

	hit->RemoveForList();
	if (hit)  delete hit;
	if (data) delete data;

}

//---------------------------------------------------------------------------
//CHARA_OBJECT：初期処理
//---------------------------------------------------------------------------
void CHARA_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//CHARA_OBJECT：終了処理
//---------------------------------------------------------------------------
void CHARA_OBJECT::Finalize() {



}
//---------------------------------------------------------------------------
//CHARA_OBJECT：更新処理
//---------------------------------------------------------------------------
void CHARA_OBJECT::Update() {

	data->move = VEC2D(0, 0);
	data->KnockBackTime -= 1.0;
	if (data->KnockBackTime < 0) data->KnockBackTime = 0;
	data->DamageIgnoreTime -= 1.0;
	if (data->DamageIgnoreTime < 0) data->DamageIgnoreTime = 0;
	MoveKnockBack();

	if (data->health < 0) {
		data->health = 0;
		data->islive = false;
	}

	if (data->islive == false) {
		data->deathcount++;
	}
	if (data->deathcount > 32) {
		Kill();
	}
	
}

void CHARA_OBJECT::Think() {



}

void CHARA_OBJECT::Collision() {

	data->pos = data->pos + data->move;

}

//---------------------------------------------------------------------------
//CHARA_OBJECT：描画処理
//---------------------------------------------------------------------------
void CHARA_OBJECT::Draw() {

	//DrawCircleAA((float)data->pos.x - common->camera->GetCameraPos().x, (float)data->pos.y - common->camera->GetCameraPos().y, 16.0, 32, GetColor(255, 0, 255), 1);

}

void CHARA_OBJECT::InputItr(int itrnum) {
	itr = itrnum;
}

void CHARA_OBJECT::InputMgr(CHARA_OBJMGR *mgrpointer) {
	this->mgrp = mgrpointer;
}

void CHARA_OBJECT::WallCheck() {
	hit->UpdateMoveObj(&data->move);
}

void CHARA_OBJECT::Kill() {
	mgrp->RemoveChara(itr);
	data->islive = false;
}

int CHARA_OBJECT::IgnoreDefDamage(double value, bool isignoretime) {

	data->health -= (int)value;
	data->DamageIgnoreTime = data->IgnoreDamageCT;
	return (int)value;

}

int CHARA_OBJECT::Damage(double value, bool isignoretime) {

	//(防御力)%だけダメージを軽減
	if (data->DamageIgnoreTime > 0 && isignoretime == false) return 0;
	int dm = (int)value * ((100.0 - data->deffence) / 100.0);

	data->health -= dm;
	data->DamageIgnoreTime = data->IgnoreDamageCT;
	return dm;

}

void CHARA_OBJECT::DrawDeath() {

	if (data->isDeathSmoke == false) return;
	data->GrHandle = mgrp->GetGrHandle(8);
	DrawRectGraph(data->pos.x - 16 - common->camera->GetCameraPos().x, data->pos.y - 16 - common->camera->GetCameraPos().y, 32* (data->deathcount / 8), 0, 32, 32, data->GrHandle, true, false);

}

int CHARA_OBJECT::Damage(double motion, double strength, bool isignoretime) {

	if (data->DamageIgnoreTime > 0 && isignoretime == false) return 0;

	double damage;
	damage = (strength / 100.0) * motion;
	data->DamageIgnoreTime = data->IgnoreDamageCT;
	return Damage(damage, isignoretime);

}

void CHARA_OBJECT::KnockBack(VEC2D *m) {

	if (data->KnockBackTime > 0) return;
	if (data->DamageIgnoreTime > 0) return;

	double len = m->length();
	double deftime;

	if (len < 30) {
		deftime = 12.0;
	}
	else if (len < 100) {
		deftime = 28.0;
	}
	else if (len < 250) {
		deftime = 48.0;
	}
	else {
		deftime = 60.0;
	}

	data->KnockBack = *m / deftime;
	data->KnockBackTime = deftime * ((100.0 - data->knockback_res) / 100.0);
	data->DamageIgnoreTime = deftime + 6.0;

}

void CHARA_OBJECT::MoveKnockBack() {

	if (data->KnockBackTime == 0) {
		return;
	}
	else if (0.0 < data->KnockBackTime && data->KnockBackTime < 1.0) {
		MoveStr(&VEC2D(data->KnockBack * data->KnockBackTime));
	}
	else {
		MoveStr(&data->KnockBack);
	}

}



CHARA_DEFINFO::CHARA_DEFINFO(
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
)
{

	this->pos = *pos;
	this->move = *move;
	this->angle = angle;
	this->timer = timer;
	this->islive = islive;
	this->iscount = iscount;
	this->health = health;
	this->strength = strength;
	this->deffence = deffence;
	this->speed = speed;
	this->knockback_res = knockback_res;
	this->flag = flag;
	this->charatype = charatype;
	this->charamem = charamem;
	this->charaname = charaname;
	this->IgnoreDamageCT = IgDmgCt;

	this->KnockBackTime = 0;
	this->KnockBack = VEC2D(0, 0);
	this->DamageIgnoreTime = 0;

	this->MaxHP = health;
	this->isDeathSmoke = true;

}











CHARA_HIT* CHARA_OBJMGR::GetDefaultCharaHit(POINT2D init_pos, CharaType type) {

	if (type == None) return NULL;
	CHARA_HIT *charahit = 0;

	switch (type) {

	case Player:
		charahit = new CHARA_HIT(&init_pos, 16, Player_hit, true);
		break;

	case Sword_of_Player:
		charahit = new CHARA_HIT(&init_pos, 10, Bullet_hit, false);
		break;

	case GrayKnight:
		charahit = new CHARA_HIT(&init_pos, 16, Enemy_hit, true);
		break;

	case Sword_of_GrayKnight:
		charahit = new CHARA_HIT(&init_pos, 16, Bullet_hit, false);
		break;

	case CoronaMage:
		charahit = new CHARA_HIT(&init_pos, 16, Enemy_hit, true);
		break;

	case Sword_of_CoronaMage:
		charahit = new CHARA_HIT(&init_pos, 8, Bullet_hit, false);
		break;
			
	case Wave_of_CoronaMage:
		charahit = new CHARA_HIT(&init_pos, 15, Bullet_hit, false);
		break;
			
	case Meteor_of_CoronaMage:
		charahit = new CHARA_HIT(&init_pos, 15, Bullet_hit, false);
		break;

	case Explosion_of_meteor:
		charahit = new CHARA_HIT(&init_pos, 14, Bullet_hit, false);
		break;

	case Shadow_of_meteor:
		charahit = new CHARA_HIT(&init_pos, 1, Virtual_hit, false);
		break;

	case LateSniper:
		charahit = new CHARA_HIT(&init_pos, 16, Enemy_hit, true);
		break;

	case Bullet_of_LateSniper:
		charahit = new CHARA_HIT(&init_pos, 8, Bullet_hit, true);
		break;


	}

	return charahit;

}


CHARA_DEFINFO* CHARA_OBJMGR::GetDefaultCharaData(POINT2D init_pos, double init_angle, CharaType type) {

	if (type == None) return NULL;
	CHARA_DEFINFO *charadata = new CHARA_DEFINFO(&POINT2D(0, 0), &VEC2D(0, 0), 0, 0, true, 0, 0, 0, 0, 0, 0, 0, None, None_mem, std::string(""), 6);

	charadata->pos = init_pos;
	charadata->move = VEC2D(0, 0);
	charadata->angle = init_angle;
	charadata->timer = 0;
	charadata->deathcount = 0;

	switch (type) {

	case Player:

		charadata->deffence = 0.0;
		charadata->health = PlayerHP;
		charadata->iscount = false;
		charadata->strength = 10.0;
		charadata->speed = 4.0;
		charadata->knockback_res = 10.0;
		charadata->charatype = Player;
		charadata->charaname = "プレイヤー";
		charadata->charamem = Player_mem;
		charadata->GrHandle = this->GetGrHandle(0);
		charadata->IgnoreDamageCT = 0;

		break;


	case Sword_of_Player:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Sword_of_Player;
		charadata->charaname = "プレイヤーの剣";
		charadata->charamem = Bullet_mem;
		charadata->IgnoreDamageCT = 0;

		break;


	case GrayKnight:

		charadata->deffence = 15.0;
		charadata->health = 34;
		charadata->iscount = true;
		charadata->strength = 4.0;
		charadata->speed = 3.0;
		charadata->knockback_res = 10.0;
		charadata->charatype = GrayKnight;
		charadata->charaname = "グレイナイト";
		charadata->charamem = Enemy_mem;
		charadata->GrHandle = this->GetGrHandle(1);
		charadata->IgnoreDamageCT = 28;

		break;


	case Sword_of_GrayKnight:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Sword_of_Player;
		charadata->charaname = "グレイナイトの剣";
		charadata->charamem = Bullet_mem;
		charadata->IgnoreDamageCT = 0;

		break;


	case CoronaMage:

		charadata->deffence = 24.0;
		charadata->health = 260;
		charadata->iscount = true;
		charadata->strength = 18.0;
		charadata->speed = 3.0;
		charadata->knockback_res = 10.0;
		charadata->charatype = CoronaMage;
		charadata->charaname = "Corona Mage";
		charadata->charamem = Boss_mem;
		charadata->GrHandle = this->GetGrHandle(2);
		charadata->IgnoreDamageCT = 28;

		break;


	case Sword_of_CoronaMage:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Sword_of_CoronaMage;
		charadata->charaname = "コロナメイジの剣";
		charadata->charamem = Bullet_mem;
		charadata->GrHandle = this->GetGrHandle(3);
		charadata->IgnoreDamageCT = 0;

		break;

	case Wave_of_CoronaMage:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Wave_of_CoronaMage;
		charadata->charaname = "コロナメイジの衝撃波";
		charadata->charamem = Bullet_mem;
		charadata->GrHandle = this->GetGrHandle(4);
		charadata->IgnoreDamageCT = 0;

		break;

	case Meteor_of_CoronaMage:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Meteor_of_CoronaMage;
		charadata->charaname = "コロナメイジのメテオ";
		charadata->charamem = Bullet_mem;
		charadata->GrHandle = this->GetGrHandle(5);
		charadata->IgnoreDamageCT = 0;

		break;

	case Explosion_of_meteor:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Sword_of_Player;
		charadata->charaname = "メテオの爆発";
		charadata->charamem = Bullet_mem;
		charadata->IgnoreDamageCT = 0;

		break;


	case Shadow_of_meteor:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Shadow_of_meteor;
		charadata->charaname = "メテオの影";
		charadata->charamem = Virtual_mem;
		charadata->GrHandle = this->GetGrHandle(7);
		charadata->IgnoreDamageCT = 0;

		break;


	case LateSniper:

		charadata->deffence = 30.0;
		charadata->health = 20;
		charadata->iscount = true;
		charadata->strength = 5.0;
		charadata->speed = 4.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = LateSniper;
		charadata->charaname = "レイトスナイパー";
		charadata->charamem = Enemy_mem;
		charadata->GrHandle = this->GetGrHandle(9);
		charadata->IgnoreDamageCT = 28;

		break;


	case Bullet_of_LateSniper:

		charadata->deffence = 100.0;
		charadata->health = 99999999;
		charadata->iscount = false;
		charadata->strength = 0.0;
		charadata->speed = 0.0;
		charadata->knockback_res = 100.0;
		charadata->charatype = Bullet_of_LateSniper;
		charadata->charaname = "レイトスナイパーの弾";
		charadata->charamem = Bullet_mem;
		charadata->GrHandle = this->GetGrHandle(10);
		charadata->IgnoreDamageCT = 0;
		charadata->isDeathSmoke = false;

		break;


	}

	return charadata;

}



//キャラが消滅する際、
//上から順に描画されなくなっていき
//薄くなっていって
//点滅する