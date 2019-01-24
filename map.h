#pragma once
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <array>

#include "gclass.h"

class MAP_OBJECT;
class COMMON_DATA;
class HIT_OBJECT;

using namespace std;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class MAP_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	COMMON_DATA * common;
	std::list<MAP_OBJECT*> *map;
	POINT2D maxmap;
	std::list<int> *reset;
	int i; //�J�E���^�ϐ�
	std::ifstream stage;
	std::string str;
	int GrHandle;
	int gamestage;

		   //�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	MAP_OBJMGR(COMMON_DATA *common, int stage);	//�R���X�g���N�^

	void AddWall(WALL_HIT *wall, COMMON_DATA *common);

};

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e
//---------------------------------------------------------------------------
class MAP_OBJECT : public BASE_OBJECT {

public:

	//�����������o�ϐ�������
	WALL_HIT *hit;	//�Փ˔���I�u�W�F�N�g�̃f�[�^
	COMMON_DATA *common;
	int itr;
	MAP_OBJMGR *mgr;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	void InputItr(int itrnum);
	MAP_OBJECT(WALL_HIT *hitdata, COMMON_DATA *common, int itrnum);		//�R���X�g���N�^
	~MAP_OBJECT();	//�f�X�g���N�^

};
