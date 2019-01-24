#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "camera.h"

class COMMON_DATA;
class EFFECT_OBJECT;

enum EffectType {

	GreenEffect,
	RedEffect,
	ExplosionEffect

};

//---------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g�F�L�����̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class EFFECT_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	std::list<EFFECT_OBJECT*> *effect;
	std::list<int> *reset;
	std::vector<int> *GrHandle;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	EFFECT_OBJMGR(COMMON_DATA *common);	//�R���X�g���N�^

	void AddEffect(EFFECT_OBJECT *effectdata);	//�G��ǉ�����
	void RemoveEffect(int itrnum);	//�G���폜����

	void GetDefaultEffect(EFFECT_OBJECT *enemy, int type, POINT2D *pos);
	void InitGr();
	int GetGrHandle(int a) { return GrHandle->at(a); };

private:
	void ResetListElement();

};

//---------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g�F�L�����i���ۃN���X�j
//---------------------------------------------------------------------------
class EFFECT_OBJECT : public BASE_OBJECT {

public:

	//�����������o�ϐ�������
	int itrnum;
	EFFECT_OBJMGR *mgrp;
	int timer;
	POINT2D pos;
	EffectType type;
	int GrHandle;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	void InputItr(int itrnum);
	void InputMgr(EFFECT_OBJMGR *mgrpointer);
	void RemoveForList();
	EFFECT_OBJECT(EffectType type, int ofset, COMMON_DATA *common, POINT2D *pos);		//�R���X�g���N�^
	~EFFECT_OBJECT();	//�f�X�g���N�^

};
