#pragma once

#include <vector>
#include <list>

#include "gclass.h"

class COMMON_DATA;
class KEY_INFO;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class GAME_CLEAR : public BASE_GAMESC {

public:
	//�����������o�ϐ�������
	int time;
	int GrHandle;
	int font;
	int font2;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	GAME_CLEAR(GAME *gamemgr, COMMON_DATA *common);	//�R���X�g���N�^

};
