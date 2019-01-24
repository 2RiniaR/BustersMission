#include "DxLib.h"
#include "sceneMGR.h"
#include "key.h"
#include "gconf.h"
#include "config.h"

//�������������������������R���X�g���N�^��������������������������������������������������������������������������������������������
CONFIG::CONFIG(SCENE_CHANGER* changer) : BASE_SCENE(changer) {



}

//������������������������������������������������������
void CONFIG::Initialize(){

	Fonthandle_Config = CreateFontToHandle("TypeOne Regular", 48, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8); //�����j���[�̃t�H���g�n���h��

}

//�������������������������I����������������������������
void CONFIG::Finalize() {

	InitFontToHandle(); //���ׂẴt�H���g�f�[�^�̍폜

}

//�������������������������X�V��������������������������
void CONFIG::Update() {

	if ( key->GetKeyStatus(KEY_INPUT_UP) == 1 ) {
		select = (select + 2) % 3;
	}

	if ( key->GetKeyStatus(KEY_INPUT_DOWN) == 1 ) {
		select = (select + 1) % 3;
	}

	if ( key->GetKeyStatus(KEY_INPUT_RIGHT) == 1 ) {

		if (select == 0) {

			game_config->ChangeBGMVolume( game_config->GetBGMVolume() + 1 );
			if ( game_config->GetBGMVolume() > 10 ) { game_config->ChangeBGMVolume(10); }

		}
		else if (select == 1) {

			game_config->ChangeSEVolume(game_config->GetSEVolume() + 1);
			if (game_config->GetSEVolume() > 10) { game_config->ChangeSEVolume(10); }

		}

	}

	if ( key->GetKeyStatus(KEY_INPUT_LEFT) == 1 ) {

		if (select == 0) {

			game_config->ChangeBGMVolume(game_config->GetBGMVolume() - 1);
			if (game_config->GetBGMVolume() < 0) { game_config->ChangeBGMVolume(0); }

		}
		else if (select == 1) {

			game_config->ChangeSEVolume(game_config->GetSEVolume() - 1);
			if (game_config->GetSEVolume() < 0) { game_config->ChangeSEVolume(0); }

		}

	}

	if ( key->GetKeyStatus(KEY_INPUT_Z) == 1 ) {

		if (select == 2) { mSceneChanger->ChangeSceneWithFade(eScene_Start); }

	}

}

//�������������������������`�恡������������������������
void CONFIG::Draw() {

	//���̔w�i�̕`��
	DrawBox(0, 0, 800, 600, GetColor(200, 255, 255), TRUE);

	DrawFormatStringToHandle(150, 125, GetColor(0, 0, 0), Fonthandle_Config, "BGM VOLUME");
	DrawFormatStringToHandle(150, 225, GetColor(0, 0, 0), Fonthandle_Config, "SE VOLUME");
	DrawFormatStringToHandle(150, 325, GetColor(0, 0, 0), Fonthandle_Config, "BACK");

	DrawFormatStringToHandle(90, 125 + (select * 100), GetColor(0, 0, 255), Fonthandle_Config, ">");
	DrawFormatStringToHandle(700, 125, GetColor(80, 80, 80), Fonthandle_Config, "%d", game_config->GetBGMVolume());
	DrawFormatStringToHandle(700, 225, GetColor(80, 80, 80), Fonthandle_Config, "%d", game_config->GetSEVolume());


}