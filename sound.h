#pragma once
#include <vector>
#include <list>

#include "gclass.h"

class SOUND_OBJECT;
class COMMON_DATA;
class HIT_OBJECT;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class SOUND_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	COMMON_DATA * common;
	std::list<SOUND_OBJECT> *sound;
	std::list<int> *reset;
	int i; //�J�E���^�ϐ�

		   //�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	SOUND_OBJMGR(COMMON_DATA *common);	//�R���X�g���N�^

	void AddSound(int type);	//�G��ǉ�����
	void RemoveSound(int itrnum);	//�G���폜����

};

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e
//---------------------------------------------------------------------------
class SOUND_OBJECT : public BASE_OBJECT {

public:

	//�����������o�ϐ�������
	HIT_OBJECT * hit;	//�Փ˔���I�u�W�F�N�g�̃f�[�^
	int type;
	COMMON_DATA *common;
	int itr;
	SOUND_OBJMGR *mgr;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	void InputItr(int itrnum);
	SOUND_OBJECT(int type, COMMON_DATA *common, int itrnum);		//�R���X�g���N�^
	~SOUND_OBJECT();	//�f�X�g���N�^

};
