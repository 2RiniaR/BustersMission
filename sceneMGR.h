#pragma once

class GAME_CONFIG;
class KEY_INFO;

#define EXT 1

//----------------------------------------------------------
// �V�[���̗񋓑�
//----------------------------------------------------------
enum eScene{

	eScene_Start,   //�X�^�[�g
	eScene_Config,  //�ݒ�
	eScene_Game,    //�Q�[��
	eScene_Result,

	eScene_None    //����

};

enum eFade {

	eFade_in,
	eFade_stay,
	eFade_out

};

//----------------------------------------------------------
// TASK �N���X
//----------------------------------------------------------
class TASK {

public:
	GAME_CONFIG *game_config;		//�Q�[���ݒ���
	KEY_INFO *key;					//�L�[���̊i�[
	int *GameStage;
	int *PlayerScore;
	int *LeftTime;
	int *LeftLife;

	virtual ~TASK() {}
	virtual void Initialize() {}    //����������
	virtual void Finalize() {}		//�I������
	virtual void Update() = 0;		//�X�V����
	virtual void Draw() = 0;		//�`�揈��

	void GameStageSet(int stage) { *GameStage = stage; };

};

//----------------------------------------------------------
// SCENE_CHANGER �N���X
//----------------------------------------------------------
class SCENE_CHANGER {

public:
	virtual void ChangeScene(eScene NextScene) = 0;			//�w��V�[���ɕύX����
	virtual void ChangeSceneWithFade(eScene NextScene) = 0;	//�t�F�[�h��������Ŏw��V�[���ɕύX����
	virtual void SceneUpdate() = 0;

};

//----------------------------------------------------------
// FADE_MGR �N���X
//----------------------------------------------------------
class FADE_MGR {

public:
	FADE_MGR() { mFade = eFade_stay, bright = 255; };
	eScene fNextScene;

protected:
	int bright;
	eFade mFade;
	virtual void FadeIn() = 0;
	virtual void FadeOut() = 0;
	void Change_Fade(eFade NextFade) { mFade = NextFade; };

};

//----------------------------------------------------------
// BASE_SCENE �N���X
//----------------------------------------------------------
class BASE_SCENE :public TASK{

protected:
	SCENE_CHANGER *mSceneChanger;	//�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
	BASE_SCENE(SCENE_CHANGER* changer) { mSceneChanger = changer; };
	virtual ~BASE_SCENE() {}
	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update() {};
	virtual void Draw() {};

};

//----------------------------------------------------------
// SCENE_MGR �N���X
//----------------------------------------------------------
class SCENE_MGR : public SCENE_CHANGER, TASK, FADE_MGR{

private:
	BASE_SCENE *mScene;		//�V�[���Ǘ��ϐ�
	eScene mNextScene;		//���̃V�[���Ǘ��ϐ�

	
	void SceneUpdate();
	void FadeIn();
	void FadeOut();

public:
	SCENE_MGR();
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

	void ChangeScene(eScene NextScene);  // ���� nextScene �ɃV�[����ύX����
	void ChangeSceneWithFade(eScene NextScene);  // �t�F�[�h�����ň��� nextScene �ɃV�[����ύX����

};

double pi();
double to_deg(double r);
double to_rad(double d);
void rad_zero(double *r);