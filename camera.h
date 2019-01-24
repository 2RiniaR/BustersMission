#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "hit.h"

class COMMON_DATA;

//---------------------------------------------------------------------------
//弾オブジェクト：弾のマネージャークラス
//---------------------------------------------------------------------------
class CAMERA_OBJMGR : public BASE_OBJMGR {

public:
	//■■■メンバ変数■■■
	COMMON_DATA *common;
	POINT2D pos;
	VEC2D move;

	//■■■メンバ関数■■■
	void Initialize();
	void Finalize();
	void Update();		//更新処理
	void Draw();		//描画処理
	CAMERA_OBJMGR(COMMON_DATA *common);	//コンストラクタ

	void MoveCamera(VEC2D *v);
	POINT2D GetCameraPos() { return pos; };

};
