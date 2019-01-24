#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "hit.h"

class COMMON_DATA;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class CAMERA_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	COMMON_DATA *common;
	POINT2D pos;
	VEC2D move;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	CAMERA_OBJMGR(COMMON_DATA *common);	//�R���X�g���N�^

	void MoveCamera(VEC2D *v);
	POINT2D GetCameraPos() { return pos; };

};
