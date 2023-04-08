/*
 *	@file	PlayScene.cpp
 *	@brief  CSV�G�f�B�^
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "PlayScene.h"

#define		SCREEN_WIDTH		1000
#define		SCREEN_HEIGHT		800
#define		BLOCK_SPAWN			20

//�@�b��
#define		SECOND				60
//�@60�t���[��(1�b) �~�@�b��(SECOND)
#define		SAVE_SPAWN			60 * SECOND

//�@�u���b�N�z��
int m_MapBlock[SCREEN_WIDTH / BLOCK_SPAWN][SCREEN_HEIGHT / BLOCK_SPAWN];
int m_SaveBlock[SCREEN_WIDTH / BLOCK_SPAWN][SCREEN_HEIGHT / BLOCK_SPAWN];


 //--------------------------------------------------------//
 //�R���X�g���N�^                                          //
 //--------------------------------------------------------//
PlayScene::PlayScene() :
	Scene(),
	m_Mouse(),
	m_BlockNum(),
	m_SaveCount(),
	is_SaveFlag()
{
	//�@�}�E�X�J�[�\�����B��
	SetMouseDispFlag(false);
}

//--------------------------------------------------------//
//�f�X�g���N�^                                            //
//--------------------------------------------------------//
PlayScene::~PlayScene()
{
	InitGraph();

}

//--------------------------------------------------------//
//����������                                              //
//--------------------------------------------------------//
void PlayScene::Init(int screenWidth, int screenHeight)
{
	is_ChangeSceneFlag = false;
	is_SaveFlag = false;
	m_Mouse = { 0 };
	m_BlockNum = 0;
	m_SaveCount = 0;
}

//--------------------------------------------------------//
//�X�V����                                                //
//--------------------------------------------------------//
void PlayScene::Update(float deltaTime)
{
	//�@�I�[�g�Z�[�u
	AutoSave();

	//�@�}�E�X�̍��W�擾
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);
	m_Mouse.x = Func::Clamp(m_Mouse.x, 0, SCREEN_WIDTH);
	m_Mouse.y = Func::Clamp(m_Mouse.y, 0, SCREEN_HEIGHT);

	//�@�E�N���b�N�`��
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		m_MapBlock[m_Mouse.x / BLOCK_SPAWN][m_Mouse.y / BLOCK_SPAWN] = m_BlockNum;
	}

	//�@�z�C�[����]�Ő��l�ύX
	m_BlockNum += GetMouseWheelRotVol();
	m_BlockNum = Func::Clamp(m_BlockNum, 0, 5);

	//�@�ҏW���I�������G���^�[�ŏI��
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_RETURN))
	{
		//�@�Z�[�u�m�F
		LastExport();
		//�@�\�t�g�I��
		ExitApp();
	}
}

//--------------------------------------------------------//
//�`�揈��                                                //
//--------------------------------------------------------//
void PlayScene::Draw()
{
	DrawBoxAA(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, White, true);

	// �u���b�N
	for (int y = 0; y < (SCREEN_HEIGHT / BLOCK_SPAWN) + 10; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
		{
			//�@���l����u���b�N
			switch (m_MapBlock[x][y])
			{
			case 1:
				DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
					x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
					Blue, TRUE);
				break;
			case 2:
				DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
					x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
					Yellow, TRUE);
				break;
			case 3:
				DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
					x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
					Green, TRUE);
				break;
			case 4:
				DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
					x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
					Black, TRUE);
				break;
			case 5:
				DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
					x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
					Red, TRUE);
				break;
			}

			//�@�{�b�N�X�̘g
			DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
				x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
				Black, FALSE);
		}
	}

	//�@�}�E�X�̈ʒu
	DrawBox(m_Mouse.x - BLOCK_SPAWN / 2, m_Mouse.y - BLOCK_SPAWN / 2,
		    m_Mouse.x + BLOCK_SPAWN / 2, m_Mouse.y + BLOCK_SPAWN / 2,
		    Red, true);
	
	//�@�X�N���[�����W
	DrawFormatString(0, 30, Black, "(x,y) = (%d,%d)", m_Mouse.x, m_Mouse.y);
	//�@�u���b�N�ԍ��i�}�E�X�z�C�[����]�ʁj
	DrawFormatString(0, 60, Black, "Num = (%d)", m_BlockNum);

	//�@�Z�[�u�m�F
	if (m_SaveCount > SAVE_SPAWN + 60)
	{
		DrawFormatString(0, 120, Black, "�Z�[�u��...");
	}
	else if (m_SaveCount > SAVE_SPAWN + 30)
	{
		DrawFormatString(0, 120, Black, "�Z�[�u��..");
	}
	else if (m_SaveCount > SAVE_SPAWN)
	{
		DrawFormatString(0, 120, Black, "�Z�[�u��.");
	}
}

//--------------------------------------------------------//
//�I������                                                //
//--------------------------------------------------------//
void PlayScene::Finalize()
{

}

//--------------------------------------------------------//
//10�b��1��Z�[�u����                                     //
//--------------------------------------------------------//
void PlayScene::AutoSave()
{
	//�@�Z�[�u���͔�������
	if (is_SaveFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		if (!(m_SaveCount > SAVE_SPAWN && m_SaveCount <= SAVE_SPAWN + 1))
		{
			is_SaveFlag = false;
		}
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		if (m_SaveCount > SAVE_SPAWN && m_SaveCount <= SAVE_SPAWN + 1)
		{
			is_SaveFlag = true;
		}
	}

	//�@�ۑ��܂ŃJ�E���g�_�E��
	m_SaveCount++;
	if (m_SaveCount > SAVE_SPAWN + 60)//�@1�b�����m�F�p�ɗP�\����
	{
		m_SaveCount = 0;
	}

	//�@�z���ۑ�����
	if (m_SaveCount == SAVE_SPAWN)
	{
		for (int y = 0; y < SCREEN_HEIGHT / BLOCK_SPAWN; y++)
		{
			for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
			{
				//�@�Z�[�u�p�z��Ɍ��݂̔z���ۑ�
				m_SaveBlock[x][y] = m_MapBlock[x][y];
			}
		}
	}

	//�@�ۑ������f�[�^�ɖ߂�
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_Z))
	{
		for (int y = 0; y < SCREEN_HEIGHT / BLOCK_SPAWN; y++)
		{
			for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
			{
				m_MapBlock[x][y] = m_SaveBlock[x][y];
			}
		}
	}
}

//�@�G�N�X�|�[�g�p�C���N���[�h
#include <fstream>
//--------------------------------------------------------//
//CSV�ɏ����o��                                           //
//--------------------------------------------------------//
void PlayScene::ExportCSV()
{
	using namespace std;
		
	//�@��΃p�X�w��
	//string FileName = "C:/Users/it222180/Desktop/Data.csv";
	//�@���΃p�X�w��
	string FileName = "Resources/SaveData/Data.csv";

	//�@�t�@�C�����J��
	ofstream ofs(FileName);

	//�@�P�s�����������玟�̗��
	for (int y = 0; y < SCREEN_HEIGHT / BLOCK_SPAWN; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
		{
			ofs << m_MapBlock[x][y] << ",";
		}
		ofs << endl;
	}

	//�@�t�@�C�������
	ofs.close();
}

//--------------------------------------------------------//
//�Ō�ɏ����o��                                          //
//--------------------------------------------------------//
void PlayScene::LastExport()
{
	//�@�Ō�ɏ����o����
	int isSave;

	//�@���b�Z�[�W�{�b�N�X�̕\��
	isSave = MessageBox(
		NULL,
		TEXT("�ۑ����ďI���܂���?"),
		TEXT("�m�F"),
		MB_YESNO | MB_ICONQUESTION);

	//�@Yes�Ȃ�Εۑ�����
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}
