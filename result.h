#pragma once

#include "sceneMGR.h"

class BASE_SCENE;
class SCENE_CHANGER;

class RESULT : public BASE_SCENE {

private:
	int time;
	int lefttime;
	int life;
	int score;
	int stage;
	int GrHandle;
	int font;

public:
	RESULT(int time, int life, int score, int stage, SCENE_CHANGER* changer);
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};