#pragma once

class BASE_SCENE;
class SCENE_CHANGER;

class START : public BASE_SCENE {

private:
	int Fonthandle_Menu;	//���j���[�Ɏg�p����t�H���g
	int select;				//�I�𒆂̍���
	int GrHandle;			//�X�^�[�g��ʂ̔w�i
	int CarsolGr;

public:
	START(SCENE_CHANGER* changer);
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};