#include <vector>
#include <string.h>
#include <math.h>
#include "DxLib.h"
#include "sceneMGR.h"
#include "start.h"
#include "config.h"
#include "game.h"
#include "result.h"
#include "key.h"
#include "gconf.h"


//�������������������������R���X�g���N�^��������������������������������������������������������������������������������������������
SCENE_MGR::SCENE_MGR() :mNextScene(eScene_None){ //���̃V�[���Ǘ��ϐ�

	mScene = (BASE_SCENE*) new START(this);
	game_config = new GAME_CONFIG;
	key = new KEY_INFO;
	mScene->game_config = this->game_config;	//�Q�[���ݒ���̑��
	mScene->key = this->key;					//�L�[���̑��
	GameStage = new int;
	*GameStage = 1;
	PlayerScore = new int;
	*PlayerScore = 0;
	LeftLife = new int;
	*LeftLife = 0;
	LeftTime = new int;
	*LeftTime = 0;

}

//��������������������������������������������������������������������������������������������������������������������������
void SCENE_MGR::Initialize() {

	mScene->Initialize();

}

//�������������������������I��������������������������������������������������������������������������������������������������
void SCENE_MGR::Finalize() {

	mScene->Finalize();
	delete game_config;

}

//�������������������������X�V��������������������������������������������������������������������������������������������
void SCENE_MGR::Update() {

	SceneUpdate();	//Scene�̕ύX������Ă����ꍇ�AmScene��ύX
	key->UpdateKey();

	switch (mFade) {

	case eFade_in:
		FadeIn();
		break;

	case eFade_out:
		FadeOut();
		break;

	case eFade_stay:
		mScene->Update(); //�V�[���̍X�V
		break;

	}
	
}

//�������������������������`�恡������������������������������������������������������������������������������������������
void SCENE_MGR::Draw() {
	
	mScene->Draw(); //�V�[���̕`��

}

//�������������������������V�[���̕ύX��������������������������������������������������������������������������������������������
void SCENE_MGR::SceneUpdate() {

	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����

		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;

		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�

		case eScene_Start:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BASE_SCENE*) new START(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���

		case eScene_Config:
			mScene = (BASE_SCENE*) new CONFIG(this);
			break;

		case eScene_Game:
			mScene = (BASE_SCENE*) new GAME(LeftTime, LeftLife, PlayerScore, GameStage, this);
			break;

		case eScene_Result:
			mScene = (BASE_SCENE*) new RESULT(*LeftTime, *LeftLife, *PlayerScore, *GameStage, this);
			break;

		}

		mNextScene = eScene_None;					//���̃V�[�������N���A
		mScene->game_config = this->game_config;	//�Q�[���ݒ���̑��
		mScene->key = this->key;					//�L�[���̑��
		mScene->GameStage = this->GameStage;
		mScene->LeftLife = this->LeftLife;
		mScene->LeftTime = this->LeftTime;
		mScene->PlayerScore = this->PlayerScore;
		mScene->Initialize();						//�V�[����������

	}

}

//������������������������ChangeScene()��������������������������������������������������������������������������������������������
void SCENE_MGR::ChangeScene(eScene NextScene) {

	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
	

}

void SCENE_MGR::ChangeSceneWithFade(eScene NextScene) {

	Change_Fade(eFade_out);
	fNextScene = NextScene;

}

//�������������������������t�F�[�h�C����������������������������������������������������������������������������������������������
void SCENE_MGR::FadeIn() {

	bright += 10;
	if (bright > 255) { bright = 255, Change_Fade(eFade_stay); }
	SetDrawBright(bright, bright, bright);

}

//�������������������������t�F�[�h�A�E�g��������������������������������������������������������������������������������������������
void SCENE_MGR::FadeOut() {

	bright -= 10;
	if (bright < 0) { bright = 0, Change_Fade(eFade_in), ChangeScene(fNextScene); }
	SetDrawBright(bright, bright, bright);

}

//----------------------------------------------------------------------------------------

double pi(void) {

	return atan(1.0) * 4.0;

}

double to_deg(double r) {

	return r * 180.0 / (atan(1.0) * 4.0);

}

double to_rad(double d) {

	return (atan(1.0) * 4.0) * d / 180.0;

}

void rad_zero(double *r) {

	//�p�x�͈̔͂�0����2�΂܂łɐ���

	if (*r < 0.0) {
		*r = 2 * pi() + *r;
	}
	else if (*r > 2 * pi()) {
		*r = *r - 2 * pi();
	}
	else {
		*r = *r;
	}

}