#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "hit.h"
#include "map.h"

using namespace std;

//---------------------------------------------------------------------------
//MAP_OBJMGR：コンストラクタ
//---------------------------------------------------------------------------
MAP_OBJMGR::MAP_OBJMGR(COMMON_DATA *common, int stage)
	//BGM(array<int, 3>{LoadSoundMem("data/sound/bgm/Dungeon-Cave_loop.ogg"), LoadSoundMem("data/sound/bgm/Es-STAGE1_loop.ogg"), LoadSoundMem("data/sound/bgm/RRR_loop.ogg")})
{

	this->common = common;
	map = new std::list<MAP_OBJECT*>;
	reset = new std::list<int>;
	common->map = this;
	gamestage = stage;

}

//---------------------------------------------------------------------------
//MAP_OBJMGR：初期処理
//---------------------------------------------------------------------------
void MAP_OBJMGR::Initialize() {
	
	switch (gamestage) {

	case 1:
		stage.open("data/map/stage1.txt");
		GrHandle = LoadGraph("data/map/stage1.png");
		maxmap = POINT2D(1280, 720);
		break;

	case 2:
		stage.open("data/map/stage2.txt");
		GrHandle = LoadGraph("data/map/stage2.png");
		maxmap = POINT2D(2000, 1000);
		break;

	case 3:
		stage.open("data/map/stage3.txt");
		GrHandle = LoadGraph("data/map/stage3.png");
		maxmap = POINT2D(1280, 720);
		break;

	}

	while (getline(stage, str)) {

		double X0, Y0, X1, Y1;

		sscanf_s(str.data(), "%lf,%lf,%lf,%lf\n", &X0, &Y0, &X1, &Y1);
		POINT2D* start = new POINT2D(X0, Y0);
		POINT2D* end = new POINT2D(X1, Y1);

		WALL_HIT *wallvec = new WALL_HIT(start, end);
		AddWall(wallvec, common);

	};
	

//	WALL_HIT *wallvec = new WALL_HIT(&POINT2D(1000,100), &POINT2D(0,100));
//	AddWall(wallvec, common);


	if (map->empty() == false) {
		for (auto itr = map->begin(); itr != map->end(); ++itr) {
			(*itr)->Initialize();
		}
	}


}

//---------------------------------------------------------------------------
//MAP_OBJMGR：終了処理
//---------------------------------------------------------------------------
void MAP_OBJMGR::Finalize() {

	if (map->empty() == false) {
		for (auto itr = map->begin(); itr != map->end(); ++itr) {
			(*itr)->Finalize();
			if(*itr) delete (*itr);
		}
	}

	stage.close();

}

//---------------------------------------------------------------------------
//MAP_OBJMGR：更新処理
//---------------------------------------------------------------------------
void MAP_OBJMGR::Update() {

	int i = 0;

	if (map->empty() == false) {
		for (auto itr = map->begin(); itr != map->end(); ++itr) {
			(*itr)->InputItr(i);
			(*itr)->Update();
			i++;
		}
	}

	//削除リストresetに入っている弾データを一括削除
	if (reset->empty() == false) {

		reset->sort();
		auto itr_reset = reset->begin();
		i = 0;

		for (auto itr = map->begin(); itr != map->end();) {

			if (*itr_reset == i) {

				itr = map->erase(itr);
				itr_reset++;

			}
			else {
				++itr;
			}
			i++;

		}

		reset->clear();

	}

}

//---------------------------------------------------------------------------
//MAP_OBJMGR：描画処理
//---------------------------------------------------------------------------
void MAP_OBJMGR::Draw() {

	DrawRectGraph(0, 0, common->camera->GetCameraPos().x, common->camera->GetCameraPos().y, GAMESCREEN_X, GAMESCREEN_Y, GrHandle, false, false);

	if (map->empty() == false) {
		for (auto itr = map->begin(); itr != map->end(); ++itr) {
			(*itr)->Draw();
		}
	}

}

//---------------------------------------------------------------------------
//MAP_OBJMGR：壁の追加
//---------------------------------------------------------------------------
void MAP_OBJMGR::AddWall(WALL_HIT *wall, COMMON_DATA *common) {

	MAP_OBJECT *newwall = new MAP_OBJECT(wall, common, 0);
	map->push_back(newwall);
	common->hit->Add(newwall->hit);

}


//---------------------------------------------------------------------------
//MAP_OBJECT：イニシャライザ
//---------------------------------------------------------------------------
MAP_OBJECT::MAP_OBJECT(WALL_HIT *hitdata, COMMON_DATA *common, int itrnum) {

	this->hit = hitdata;
	this->common = common;
	itr = itrnum;

}

//---------------------------------------------------------------------------
//MAP_OBJECT：デストラクタ
//---------------------------------------------------------------------------
MAP_OBJECT::~MAP_OBJECT() {}

//---------------------------------------------------------------------------
//MAP_OBJECT：初期処理
//---------------------------------------------------------------------------
void MAP_OBJECT::Initialize() {



}

//---------------------------------------------------------------------------
//MAP_OBJECT：終了処理
//---------------------------------------------------------------------------
void MAP_OBJECT::Finalize() {

	

}
//---------------------------------------------------------------------------
//MAP_OBJECT：更新処理
//---------------------------------------------------------------------------
void MAP_OBJECT::Update() {



}

//---------------------------------------------------------------------------
//MAP_OBJECT：描画処理
//---------------------------------------------------------------------------
void MAP_OBJECT::Draw() {

	

}

void MAP_OBJECT::InputItr(int itrnum) {

	itr = itrnum;

}
