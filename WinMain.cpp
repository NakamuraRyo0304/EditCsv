/*
 *	@file	WinMain.cpp
 *	@brief	�v���O�����̃G���g���[�|�C���g�ƁA
            �Q�[���̃��C�����[�v���`����t�@�C���B
 *	@date	2021-03-15
 *  @human  KazuoHorikawa
 *  @rfact  RyoNakamura
 */

//	DxLib�G���W�����g�����߂ɕK�v�ȃC���N���[�h
#include <DxLib.h>

//	Game�N���X���g�p���邽�߂ɕK�v�ȃC���N���[�h
#include "Game/Game.h"

#include "ExtendLib/MemoryLeakDetector.h"
#include "ExtendLib/GameSystemObject/GameSystemObjects.h"

//�@�A�C�R���ύX
#include"Resources/Icon/Icon.h"

//��ʃT�C�Y
#define SCREEN_WIDTH						1000
#define SCREEN_HEIGHT						800


//	�E�B���h�E�^�C�g���ɕ\�����镶��
#define GAME_TITLE							"Edit"


//�@�������珈�����X�^�[�g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
			       LPSTR lpCmdLine, int nShowCmd)
{
	//	���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nShowCmd);

	// �E�C���h�E�^�C�g���̐ݒ�
	SetMainWindowText(GAME_TITLE);  

#if defined(_DEBUG)

	//	�������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();

#endif
	
	//	�f�o�b�O���p���O�t�@�C���͏o�͂��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);	

	//	�N�����[�h�̐ݒ�
	ChangeWindowMode(TRUE);					//	�E�C���h�E���[�h�Ŏ��s

	//	������Ԃ̉�ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	//�@�E�B���h�E�̈ʒu��ݒ�
	SetWindowPosition(350, 30);

	//�@�A�C�R���̕ύX
	SetWindowIconID(ICON_ID);

	//	DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		//�@�G���[����
		return -1;
	}

	//	��ʂ̕`����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);			

	//	���C�����[�v���Ŏg�p����ϐ���錾����
	GameSystemObjects systemObject;

	//	�Q�[���̏��������ۂɋL�q���Ă���N���X�I�u�W�F�N�g
	Game gameJobObject;						

	//	�錾�����ϐ��̏��������K�v�ł���΁A�ȉ��ōs��

	systemObject.Initialize();

	gameJobObject.SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameJobObject.SetGameSystemObject(&systemObject);

	//	�Q�[���̏������s���O�ɁA�������������s��
	gameJobObject.Init();				

	//	���C�����[�v�B
	//	ESC�L�[�������ꂽ��I��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	�����Ƀv���O�����������Ă���
		// --------------------------------------------------------------------------

		//�@�X�V�����B
		systemObject.Update();
		gameJobObject.Update();

		//	�`�揈���B
		//	��ʂ�������&�`�揈���̊J�n
		ClearDrawScreen();

		systemObject.Render();
		gameJobObject.Draw();

		//	����ʂ̓��e��\��ʂɔ��f������&�`�揈���̏I��
		ScreenFlip();

		//	�t���[�����̏����I���I
		// --------------------------------------------------------------------------
	}

	//	�v���O�������I������O�ɁA�Q�[���̏I���������s��
	gameJobObject.Finalize();				

	systemObject.Finalize();

	InitGraph();

	//	DX���C�u�����̏I������
	if (DxLib_End() == -1)
	{
		//�@�G���[����
		return -1;
	}

	//	����I��
	return 0;	
}
