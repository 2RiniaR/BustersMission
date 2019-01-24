#pragma once

#include "gclass.h"
#include "chara.h"
#include "hit.h"

class COMMON_DATA;
class CHARA_OBJECT;

//---------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g�F�v���C���[
//---------------------------------------------------------------------------
class PLAYER_OBJECT : public CHARA_OBJECT{

public:

	//�����������o�ϐ�������
	CHARA_OBJECT *sword;
	int swordcool;
	int LocalAngle;
	int Motion;
	int WalkTime;
	bool isWalk;
	bool LocalAngleChangeable;

	int DamageSound;
	int SwingSound;

	//�����������o�֐�������
	void Initialize() override;
	void Finalize() override;
	void Update() override;		//�X�V����
	void Collision();
	void Draw() override;		//�`�揈��
	void UpdateMotion();
	PLAYER_OBJECT(CHARA_HIT *hitdata, CHARA_DEFINFO *data, COMMON_DATA *common);

	POINT2D GetPlayerPos() { return data->pos; };
	void SwingSword();

};
