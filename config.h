#pragma once

class BASE_SCENE;
class SCENE_CHANGER;

class CONFIG : public BASE_SCENE {

private:
	int select;
	int Fonthandle_Config;

public:
	CONFIG(SCENE_CHANGER* changer);
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};
