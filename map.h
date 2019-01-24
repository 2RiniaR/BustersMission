#pragma once
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <array>

#include "gclass.h"

class MAP_OBJECT;
class COMMON_DATA;
class HIT_OBJECT;

using namespace std;

//---------------------------------------------------------------------------
//弾オブジェクト：弾のマネージャークラス
//---------------------------------------------------------------------------
class MAP_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	COMMON_DATA * common;
	std::list<MAP_OBJECT*> *map;
	POINT2D maxmap;
	std::list<int> *reset;
	int i; //カウンタ変数
	std::ifstream stage;
	std::string str;
	int GrHandle;
	int gamestage;

		   //■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	MAP_OBJMGR(COMMON_DATA *common, int stage);	//コンストラクタ

	void AddWall(WALL_HIT *wall, COMMON_DATA *common);

};

//---------------------------------------------------------------------------
//弾オブジェクト：弾
//---------------------------------------------------------------------------
class MAP_OBJECT : public BASE_OBJECT {

public:

	//■■■メンバ変数■■■
	WALL_HIT *hit;	//衝突判定オブジェクトのデータ
	COMMON_DATA *common;
	int itr;
	MAP_OBJMGR *mgr;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	void InputItr(int itrnum);
	MAP_OBJECT(WALL_HIT *hitdata, COMMON_DATA *common, int itrnum);		//コンストラクタ
	~MAP_OBJECT();	//デストラクタ

};
