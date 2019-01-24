#pragma once
#include <list>
#include "game.h"

class PLAYER_OBJECT;
class MAP_OBJMGR;
class KEY_INFO;
class HIT_OBJMGR;
class CAMERA_OBJMGR;
class GAME;
class CHARA_OBJMGR;
class EFFECT_OBJMGR;

class COMMON_DATA {

public:
	PLAYER_OBJECT *player;
	MAP_OBJMGR *map;
	KEY_INFO *key;
	HIT_OBJMGR *hit;
	CAMERA_OBJMGR *camera;
	CHARA_OBJMGR *chara;
	EFFECT_OBJMGR *effect;

	COMMON_DATA() {};

};

class BASE_OBJECT{

public:
	COMMON_DATA *common;

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};

class BASE_OBJMGR{

public:
	COMMON_DATA *common;

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};

class BASE_GAMESC {

public:
	COMMON_DATA *common;
	GAME *game;

	BASE_GAMESC(GAME *gamemgr) { game = gamemgr; };
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void ChangeGameScene(GameScene s) { game->ChangeGameScene(s); };
	void ChangeCommonScene(eScene s) { game->ChangeCommonScene(s); }

};