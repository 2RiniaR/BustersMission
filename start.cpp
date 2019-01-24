#include "DxLib.h"
#include "sceneMGR.h"
#include "key.h"
#include "gconf.h"
#include "start.h"

//�������������������������R���X�g���N�^��������������������������������������������������������������������������������������������
START::START(SCENE_CHANGER* changer) : BASE_SCENE(changer) {

	GrHandle = LoadGraph("data/image/other/start2.png");
	CarsolGr = LoadGraph("data/image/other/carsol.png");

}

//������������������������������������������������������
void START::Initialize() {

	select = 0;
	Fonthandle_Menu = CreateFontToHandle(NULL, 48, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8); //�����j���[�̃t�H���g�n���h��

}

//�������������������������I����������������������������
void START::Finalize() {

	InitFontToHandle(); //���ׂẴt�H���g�f�[�^�̍폜

}

//�������������������������X�V������������������������
void START::Update() {

	if (key->GetKeyStatus(KEY_INPUT_DOWN) == 1) {
		select = (select + 1) % 3;
	}

	if (key->GetKeyStatus(KEY_INPUT_UP) == 1) {
		select = (select + 2) % 3;
	}

	if (key->GetKeyStatus(KEY_INPUT_Z) == 1) {
		switch (select) {

		case 0:
			mSceneChanger->ChangeSceneWithFade(eScene_Game);
			break;
		case 1:
			mSceneChanger->ChangeSceneWithFade(eScene_Config);
			break;
		case 2:
			exit(0); //�I������
			break;
		}

	}
	
}

//�������������������������`�恡����������������������
void START::Draw() {

	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE); //�w�i�`��

	DrawExtendGraph(0, 0, 800 * EXT, 600 * EXT, GrHandle, false);

	switch (select) {

	case 0:
		DrawRectGraph(180, 380, 0, 0, 40, 40, CarsolGr, true);
		break;

	case 1:
		DrawRectGraph(180, 450, 40, 0, 40, 40, CarsolGr, true);
		break;

	case 2:
		DrawRectGraph(180, 520, 40, 0, 40, 40, CarsolGr, true);
		break;

	}

}
