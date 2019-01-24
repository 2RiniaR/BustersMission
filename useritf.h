#pragma once
#include <vector>
#include <list>

#include "gclass.h"

class COMMON_DATA;
class USERITF_OBJECT;
class USERITF_STAGE;
class USERITF_PLAYERHP;
class USERITF_BOSSHP;
class USERITF_ENEMY;
class USERITF_TIME;
class USERITF_SCORE;

//---------------------------------------------------------------------------
//弾オブジェクト：弾のマネージャークラス
//---------------------------------------------------------------------------
class USERITF_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	std::vector<USERITF_OBJECT*> *useritf;
	int stage;
	int time;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_OBJMGR(COMMON_DATA *common, int stage, int gametime);	//コンストラクタ

};

class USERITF_OBJECT :public BASE_OBJECT {

public:
	USERITF_OBJMGR *mgr;
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	USERITF_OBJECT() {};
	virtual ~USERITF_OBJECT() {};

};

class USERITF_BAR : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_BAR(COMMON_DATA *common);		//コンストラクタ
	~USERITF_BAR() {};	//デストラクタ

};

class USERITF_STAGE : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int stagename;
	int font;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_STAGE(COMMON_DATA *common, int stage);		//コンストラクタ
	~USERITF_STAGE() {};	//デストラクタ

};

class USERITF_ENEMY : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int leaveenemy;
	int font;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_ENEMY(COMMON_DATA *common);		//コンストラクタ
	~USERITF_ENEMY() {};	//デストラクタ

};

class USERITF_SCORE : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int score;
	int font;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_SCORE(COMMON_DATA *common);		//コンストラクタ
	~USERITF_SCORE() {};	//デストラクタ

};

class USERITF_TIME : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int timer;
	int font;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_TIME(COMMON_DATA *common, int gtime);		//コンストラクタ
	~USERITF_TIME() {};	//デストラクタ

};

class USERITF_PLAYERHP : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int HP;
	int font;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_PLAYERHP(COMMON_DATA *common);		//コンストラクタ
	~USERITF_PLAYERHP() {};	//デストラクタ

};

class USERITF_BOSSHP : public USERITF_OBJECT {

public:

	//■■■メンバ変数■■■
	int font;
	bool hideflag;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	USERITF_BOSSHP(COMMON_DATA *common);		//コンストラクタ
	~USERITF_BOSSHP() {};	//デストラクタ

};