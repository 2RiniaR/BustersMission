#pragma once
#include <vector>
#include <list>

#include "gclass.h"

class COMMON_DATA;
class USERITF_OBJECT;
class USERITF_STAGE;
class USERITF_PLAYERHP;
class USERITF_BOSSHP;
class USERITF_ENEMY;
class USERITF_TIME;
class USERITF_SCORE;

//---------------------------------------------------------------------------
//�e�I�u�W�F�N�g�F�e�̃}�l�[�W���[�N���X
//---------------------------------------------------------------------------
class USERITF_OBJMGR : public BASE_OBJMGR {

public:
	//�����������o�ϐ�������
	std::vector<USERITF_OBJECT*> *useritf;
	int stage;
	int time;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_OBJMGR(COMMON_DATA *common, int stage, int gametime);	//�R���X�g���N�^

};

class USERITF_OBJECT :public BASE_OBJECT {

public:
	USERITF_OBJMGR *mgr;
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	USERITF_OBJECT() {};
	virtual ~USERITF_OBJECT() {};

};

class USERITF_BAR : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_BAR(COMMON_DATA *common);		//�R���X�g���N�^
	~USERITF_BAR() {};	//�f�X�g���N�^

};

class USERITF_STAGE : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int stagename;
	int font;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_STAGE(COMMON_DATA *common, int stage);		//�R���X�g���N�^
	~USERITF_STAGE() {};	//�f�X�g���N�^

};

class USERITF_ENEMY : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int leaveenemy;
	int font;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_ENEMY(COMMON_DATA *common);		//�R���X�g���N�^
	~USERITF_ENEMY() {};	//�f�X�g���N�^

};

class USERITF_SCORE : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int score;
	int font;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_SCORE(COMMON_DATA *common);		//�R���X�g���N�^
	~USERITF_SCORE() {};	//�f�X�g���N�^

};

class USERITF_TIME : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int timer;
	int font;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_TIME(COMMON_DATA *common, int gtime);		//�R���X�g���N�^
	~USERITF_TIME() {};	//�f�X�g���N�^

};

class USERITF_PLAYERHP : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int HP;
	int font;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_PLAYERHP(COMMON_DATA *common);		//�R���X�g���N�^
	~USERITF_PLAYERHP() {};	//�f�X�g���N�^

};

class USERITF_BOSSHP : public USERITF_OBJECT {

public:

	//�����������o�ϐ�������
	int font;
	bool hideflag;

	//�����������o�֐�������
	void Initialize();
	void Finalize();
	void Update();		//�X�V����
	void Draw();		//�`�揈��
	USERITF_BOSSHP(COMMON_DATA *common);		//�R���X�g���N�^
	~USERITF_BOSSHP() {};	//�f�X�g���N�^

};