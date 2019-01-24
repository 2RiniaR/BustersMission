#pragma once
#include <vector>
#include <list>

#include "gclass.h"
#include "camera.h"

class COMMON_DATA;
class ITEM_OBJECT;

enum ItemType {

	Health5,
	Health10,
	Score10,
	Score20,
	SpeedUp1,
	StrengthUp1,
	DeffenceUp1

};

//---------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g�F�L�����̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class ITEM_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	std::list<ITEM_OBJECT*> *item;
	std::list<int> *reset;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	ITEM_OBJMGR(COMMON_DATA *common);	//�R���X�g���N�^

	void AddItem(ITEM_OBJECT *itemdata);	//�G��ǉ�����
	void RemoveItem(int itrnum);	//�G���폜����

	void GetDefaultItem(ITEM_OBJECT *enemy, int type);

private:
	void ResetListElement();

};

//---------------------------------------------------------------------------
//�Q�[���I�u�W�F�N�g�F�L�����i���ۃN���X�j
//---------------------------------------------------------------------------
class ITEM_OBJECT : public BASE_OBJECT {

public:

	//�����������o�ϐ�������
	int itrnum;
	ITEM_OBJMGR *mgrp;
	int timer;
	ItemType type;
	CHARA_HIT *hit;
	POINT2D pos;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Collision();
	void Draw();		//�`�揈��
	void InputItr(int itrnum);
	void InputMgr(ITEM_OBJMGR *mgrpointer);
	void RemoveForList();
	ITEM_OBJECT(ItemType type, POINT2D pos, double size, COMMON_DATA *common);		//�R���X�g���N�^
	~ITEM_OBJECT();	//�f�X�g���N�^

};
