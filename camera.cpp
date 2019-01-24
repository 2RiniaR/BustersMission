#include <vector>
#include <list>
#include <math.h>
#include "DxLib.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "camera.h"

CAMERA_OBJMGR::CAMERA_OBJMGR(COMMON_DATA *common) {

	this->common = common;
	common->camera = this;

}

void CAMERA_OBJMGR::Initialize() {

	POINT2D playerpos = common->player->GetPlayerPos() - POINT2D(GAMESCREEN_X / 2.0, GAMESCREEN_Y / 2.0);

	MoveCamera(&VEC2D(playerpos - pos));
	pos = pos + move;

	if (pos.x < 0) pos.x = 0;
	if (pos.x + GAMESCREEN_X > common->map->maxmap.x) pos.x = common->map->maxmap.x - GAMESCREEN_X;
	if (pos.y < 0) pos.y = 0;
	if (pos.y + GAMESCREEN_Y > common->map->maxmap.y) pos.y = common->map->maxmap.y - GAMESCREEN_Y;

	move = VEC2D(0, 0);

}

void CAMERA_OBJMGR::Finalize() {



}

void CAMERA_OBJMGR::Update() {

	POINT2D playerpos = common->player->GetPlayerPos() - POINT2D(GAMESCREEN_X / 2.0, GAMESCREEN_Y / 2.0);

	MoveCamera(&VEC2D(playerpos - pos));
	pos = pos + move;

	if (pos.x < 0) pos.x = 0;
	if (pos.x + GAMESCREEN_X > common->map->maxmap.x) pos.x = common->map->maxmap.x - GAMESCREEN_X;
	if (pos.y < 0) pos.y = 0;
	if (pos.y + GAMESCREEN_Y > common->map->maxmap.y) pos.y = common->map->maxmap.y - GAMESCREEN_Y;

	move = VEC2D(0, 0);

}

void CAMERA_OBJMGR::Draw() {



}

void CAMERA_OBJMGR::MoveCamera(VEC2D *v) {

	move = move + *v;

}