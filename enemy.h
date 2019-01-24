#pragma once

#include "hit.h"
#include "chara.h"
#include "move.h"

class HIT_OBJECT;
class COMMON_DATA;

/*
class ENEMY_BASE : public CHARA_OBJECT {

public:
	int type;
	

public:
	int GetEnemyType() { return type; };
	void Update();
	virtual void Update() = 0;
	virtual void Loop() = 0;
	virtual void Collision() = 0;
	ENEMY_BASE(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common);
	virtual ~ENEMY_BASE() {};



};
*/

class BULLET1;

class ENEMY1 :public CHARA_OBJECT {

public:
	BULLET1 *sword;
	int LocalAngle;
	int Motion;
	bool LocalAngleChangeable;

	void Update();
	void Think();
	void Collision();
	void Draw();
	ENEMY1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common);

};

class ENEMY2 :public CHARA_OBJECT {

public:
	int LocalAngle;
	int Motion;
	bool LocalAngleChangeable;
	double c;
	double bure;

	void Update();
	void Think();
	void Collision();
	void Draw();
	ENEMY2(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common);

};

class ENEMY3 :public CHARA_OBJECT {

public:
	void Update();
	void Think();
	void Collision();
	ENEMY3(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common);

};

class BOSS1 :public CHARA_OBJECT {

public:
	int LocalAngle;
	int Motion;
	int Action;
	int RunTime;
	bool parge;
	bool pargeDelta;
	bool extrem;
	bool redd;
	POINT2D playerposm;

	void Update();
	void Think();
	void Collision();
	void Draw();
	BOSS1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common);

};


class BULLET1 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;
	int LocalAngle;

	void Update();
	void Think();
	void Collision();
	BULLET1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent, int locangle);

};

class PLAYER_SWORD :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;
	int LocalAngle;

	void Update();
	void Think();
	void Collision() override;
	PLAYER_SWORD(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent, int locangle);

};

class BULLET2 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;

	void Update();
	void Think();
	void Collision() override;
	BULLET2(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);
	void Draw();

};


class BULLET3 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;
	double accel;

	void Update();
	void Think();
	void Collision() override;
	BULLET3(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);
	void Draw();

};


class BULLET4 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;


	void Update();
	void Think();
	void Collision() override;
	BULLET4(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);
	void Draw();

};


class BULLET5 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;
	double rad;

	void Update();
	void Think();
	void Collision() override;
	void Draw();
	BULLET5(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);

};


class BULLET6 :public CHARA_OBJECT {

public:
	CHARA_OBJECT *parent;

	void Update();
	void Think();
	void Collision() override;
	void Draw();
	BULLET6(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);

};

class SHADOW1 :public CHARA_OBJECT {

public:
	CHARA_OBJECT * parent;

	void Update();
	void Think();
	void Collision() override;
	void Draw();
	SHADOW1(CHARA_HIT *hitdata, CHARA_DEFINFO *enemydata, COMMON_DATA *common, CHARA_OBJECT *parent);

};