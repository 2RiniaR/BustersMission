#pragma once

#include <vector>
#include <list>

#include "gclass.h"

class COMMON_DATA;
class KEY_INFO;

//---------------------------------------------------------------------------
//弾オブジェクト：弾のマネージャークラス
//---------------------------------------------------------------------------
class GAME_CLEAR : public BASE_GAMESC {

public:
	//■■■メンバ変数■■■
	int time;
	int GrHandle;
	int font;
	int font2;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	GAME_CLEAR(GAME *gamemgr, COMMON_DATA *common);	//コンストラクタ

};
