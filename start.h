#pragma once

class BASE_SCENE;
class SCENE_CHANGER;

class START : public BASE_SCENE {

private:
	int Fonthandle_Menu;	//メニューに使用するフォント
	int select;				//選択中の項目
	int GrHandle;			//スタート画面の背景
	int CarsolGr;

public:
	START(SCENE_CHANGER* changer);
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};