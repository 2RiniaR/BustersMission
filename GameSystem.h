#pragma once

#include <vector>
#include <list>

#include "gclass.h"

class COMMON_DATA;
class KEY_INFO;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class GAME_SYSTEM: public BASE_GAMESC {

public:
	//�����������o�ϐ�������
	int GameTimer;
	int LeaveEnemy;
	int Score;
	int Stage;
	bool isPlayerLeave;

	int Pose;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	GAME_SYSTEM(GAME *gamemgr, COMMON_DATA *common, int stage);	//�R���X�g���N�^


};
