#include <vector>
#include <math.h>
#include "DxLib.h"
#include "sceneMGR.h"

#define INIT_SCREEN_W (640)
#define INIT_SCREEN_H (480)

//������������������������FPS�v��������������������������
static int mStartTime;
static int mCount;
static float mFps;
static const int N = 60;
static const int FPS = 60;

bool Flame_Count() {
	if (mCount == 0) {
		mStartTime = GetNowCount();
	}
	if (mCount == N) {
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}

//�������������������������������������E�B���h�E�̒�������������������������������������������

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	int DesktopW, DesktopH;
	double WindowExH;

	SetMainWindowText("Busters' Mission");						//�E�B���h�E�̃^�C�g����ݒ肷��
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);		//�T�C�Y�ύX���\�ɂ���
	ChangeWindowMode(FALSE);							//�E�B���h�E���[�h��L���ɂ���
	//SetWindowStyleMode(0);							//�ő剻�{�^�������݂��A����ɘg���ׂ��Ȃ�E�B���h�E���[�h�ɕύX
	//GetDefaultState(&DesktopW, &DesktopH, NULL);	 //��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
	SetGraphMode(800, 600, 16);
	//SetWindowPosition((DesktopW - INIT_SCREEN_W) / 2, (DesktopH - INIT_SCREEN_H) / 2);//�E�B���h�E�̈ʒu����ʂ̒��S�ɂ���

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;
	}							// �G���[���N�����璼���ɏI��

	//WindowExH = ((double)DesktopH - 100.0) / 480.0;
	//SetWindowMaxSize(DesktopW, DesktopH);
	//SetWindowMinSize(DesktopW / 3, DesktopH / 3);
	SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E�̗���ʐݒ�

	
	SCENE_MGR scene_mgr;
	scene_mgr.Initialize();	//������

	//�����������������������������������������������C�����[�v��������������������������������������������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		Flame_Count();
		scene_mgr.Update();  //�X�V
		scene_mgr.Draw();    //�`��
		Wait();

	}

	//����������������������������������������������������������������������������������������������������

	scene_mgr.Finalize();	//�I������

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 

}
