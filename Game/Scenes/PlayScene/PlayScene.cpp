/*
 *	@file	PlayScene.cpp
 *	@brief  CSV�G�f�B�^
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "PlayScene.h"

//�@�X�N���[���T�C�Y
#define		SCREEN_WIDTH		1000
#define		SCREEN_HEIGHT		800

//�@�b��
#define		SECOND				60
//�@�t���[����
#define		FRAME				60
//�@60�t���[��(1�b) �~�@�b��(SECOND)
#define		SAVE_SPAWN			FRAME * SECOND

//�@�i���o�[�̍ő�l
#define		MAX_NUMBER			10

//�@�u���b�N
#define		BLOCK_DEFAULT		20
//�@�u���b�N��
typedef struct { int x, y; }STAGESIZE;
STAGESIZE STAGE_SIZE = { 500,400 };

 //--------------------------------------------------------//
 //�R���X�g���N�^                                          //
 //--------------------------------------------------------//
PlayScene::PlayScene() :
	Scene(),
	m_Mouse(),
	m_BlockNum(),
	m_SaveCount(),
	is_SaveFlag(),
	m_NowColor(),
	m_Move(),
	m_CenterPos(),
	m_BlockSize()
{
	//�@�}�E�X�J�[�\�����B��
	SetMouseDispFlag(false);
	m_BlockSize = BLOCK_DEFAULT;
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
	m_Move = { 0 };
	m_CenterPos = { 0 };
	m_BlockNum = 0;
	m_SaveCount = 0;
	m_BlockSize = BLOCK_DEFAULT;

	//�@�ϒ��z��̏�����
	std::vector<int>tmp((int)STAGE_SIZE.x, 0);
	m_MapBlock = std::vector < std::vector<int>>((int)STAGE_SIZE.y, tmp);
	m_SaveBlock = m_MapBlock;
}

//--------------------------------------------------------//
//�X�V����                                                //
//--------------------------------------------------------//
void PlayScene::Update(float deltaTime)
{
	//�@�I�[�g�Z�[�u
	AutoSave();

	//�@�F�̕ύX
	ChangeBlockColor();

	//�@�}�E�X�̍��W�擾
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);
	
	//�@�E�N���b�N�`��
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		//�@�z��͈͊O�ɃA�N�Z�X���Ȃ�
		if (m_Mouse.x < 0 || m_Mouse.y < 0) return;

		m_MapBlock[(m_Mouse.y + m_Move.y) / m_BlockSize][(m_Mouse.x + m_Move.x) / m_BlockSize] = m_BlockNum;
	}

	//�@�͈͊O�ɍs���Ȃ��悤�ɂ���
	m_Mouse.x = Func::Clamp(m_Mouse.x, 0, SCREEN_WIDTH - m_BlockSize / 2);
	m_Mouse.y = Func::Clamp(m_Mouse.y, 0, SCREEN_HEIGHT - m_BlockSize / 2);

	//�@�z�C�[����SHIFT�Ń}�X��傫������
	if (pGameSystem->GetInputSystem().IsKeyDown(KEY_INPUT_LSHIFT))
	{
		//�@�z�C�[����]�Ŋg��k��
		m_BlockSize += GetMouseWheelRotVol();
		m_BlockSize = Func::Clamp(m_BlockSize, BLOCK_DEFAULT, BLOCK_DEFAULT * 10);
	}
	else
	{
		//�@�z�C�[����]�Ő��l�ύX
		m_BlockNum += GetMouseWheelRotVol();
		m_BlockNum = Func::Clamp(m_BlockNum, 0, MAX_NUMBER);
	}

	//�@�ҏW���I�������G���^�[�ŏI��
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_RETURN))
	{
		//�@�Z�[�u�m�F
		LastCheck();
	}

	//�@�\�t�g�I��
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_ESCAPE))
	{
		ExitApp();
	}

	//�@�}�X�̈ړ�
	BlockMove();
}

//--------------------------------------------------------//
//�`�揈��                                                //
//--------------------------------------------------------//
void PlayScene::Draw()
{
	DrawBoxAA(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, White, true);

	// �u���b�N
	for (int y = 0; y < m_MapBlock.size(); y++)
	{
		for (int x = 0; x < m_MapBlock[y].size(); x++)
		{
			//�@���l����u���b�N
			switch (m_MapBlock[y][x])
			{
			case 1:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Blue, TRUE);
				break;
			case 2:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Yellow, TRUE);
				break;
			case 3:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Green, TRUE);
				break;
			case 4:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Black, TRUE);	
				break;
			case 5:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Red, TRUE);
				break;
			case 6:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Purple, TRUE);
				break;
			case 7:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Orange, TRUE);
				break;
			case 8:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					DeepPink, TRUE);
				break;
			case 9:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Aqua, TRUE);
				break;
			case 10:
				DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
					x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
					Brown, TRUE);
				break;
			}

			//�@�{�b�N�X�̘g
			DrawBox(x * m_BlockSize - m_Move.x, y * m_BlockSize - m_Move.y,
				x * m_BlockSize + m_BlockSize - m_Move.x, y * m_BlockSize + m_BlockSize - m_Move.y,
				Gray, FALSE);
		}
	}

	//�@�}�E�X�̈ʒu
	DrawBox(m_Mouse.x - m_BlockSize / 2 - 1, m_Mouse.y - m_BlockSize / 2 - 1,
		m_Mouse.x + m_BlockSize / 2 + 1, m_Mouse.y + m_BlockSize / 2 + 1,
		Black, true);
	DrawBox(m_Mouse.x - m_BlockSize / 2, m_Mouse.y - m_BlockSize / 2,
		m_Mouse.x + m_BlockSize / 2, m_Mouse.y + m_BlockSize / 2,
		m_NowColor, true);

	//�@�f�o�b�O�������
	DebugText();
}

//--------------------------------------------------------//
//�I������                                                //
//--------------------------------------------------------//
void PlayScene::Finalize()
{
	if (m_MapBlock == m_SaveBlock) return;

	//�@�Ō�ɏ����o����
	int isSave;

	//�@���b�Z�[�W�{�b�N�X�̕\��
	isSave = MessageBox(
		NULL,
		TEXT("�ύX���ۑ�����Ă��܂���B\n�ۑ����܂����H"),
		TEXT("�ŏI�m�F"),
		MB_YESNO | MB_ICONQUESTION);

	//�@Yes�Ȃ�Εۑ�����
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}

//--------------------------------------------------------//
//�f�o�b�O�p����                                          //
//--------------------------------------------------------//
void PlayScene::DebugText()
{
	//�@�X�N���[�����W
	DrawFormatString(20, 30, Black, "(x,y) = (%d,%d)", m_Mouse.x, m_Mouse.y);
	//�@�u���b�N�ԍ��i�}�E�X�z�C�[����]�ʁj
	DrawFormatString(20, 60, Black, "Num = (%d)", m_BlockNum);
	//�@�Z�[�u�܂ł̃J�E���g
	if ((SAVE_SPAWN - m_SaveCount) / SECOND > 0)
	{
		DrawFormatString(20, 90, Black, "AutoSave:%d", (SAVE_SPAWN - m_SaveCount) / SECOND);
	}

	//�@�Z�[�u�m�F
	if		(m_SaveCount > SAVE_SPAWN + (2 * FRAME))
	{
		DrawFormatString(20, 120, Black, "�Z�[�u��...");
	}
	else if (m_SaveCount > SAVE_SPAWN + (1 * FRAME))
	{
		DrawFormatString(20, 120, Black, "�Z�[�u��..");
	}
	else if (m_SaveCount > SAVE_SPAWN + (0 * FRAME))
	{
		DrawFormatString(20, 120, Black, "�Z�[�u��.");
	}
}

//--------------------------------------------------------//
//�F�̕ύX                                                //
//--------------------------------------------------------//
void PlayScene::ChangeBlockColor()
{
	//�@�u���b�N�̐F�ύX
	switch (m_BlockNum)
	{
	case 1:
		m_NowColor = Blue;
		break;
	case 2:
		m_NowColor = Yellow;
		break;
	case 3:
		m_NowColor = Green;
		break;
	case 4:
		m_NowColor = Black;
		break;
	case 5:
		m_NowColor = Red;
		break;
	case 6:
		m_NowColor = Purple;
		break;
	case 7:
		m_NowColor = Orange;
		break;
	case 8:
		m_NowColor = DeepPink;
		break;
	case 9:
		m_NowColor = Aqua;
		break;
	case 10:
		m_NowColor = Brown;
		break;
	default:
		m_NowColor = White;
		break;
	}
}

//--------------------------------------------------------//
//�}�X���ړ�������                                        //
//--------------------------------------------------------//
void PlayScene::BlockMove()
{
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);

	m_CenterPos = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2};

	if (GetMouseInput() & MOUSE_INPUT_MIDDLE)
	{
		if (m_CenterPos.x > m_Mouse.x)
		{
			if (m_Move.x < 0)return;
			m_Move.x -= 5;
		}
		if (m_CenterPos.x < m_Mouse.x)
		{
			m_Move.x += 5;
		}
		if (m_CenterPos.y > m_Mouse.y)
		{
			if (m_Move.y < 0)return;
			m_Move.y -= 5;
		}
		if (m_CenterPos.y < m_Mouse.y)
		{
			m_Move.y += 5;
		}
	}

	m_Move.x = Func::Clamp(m_Move.x, 0, STAGE_SIZE.x * m_BlockSize - SCREEN_WIDTH);
	m_Move.y = Func::Clamp(m_Move.y, 0, STAGE_SIZE.y * m_BlockSize - SCREEN_WIDTH);
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
	if (m_SaveCount > SAVE_SPAWN + 180)
	{
		m_SaveCount = 0;
	}

	//�@�z���ۑ�����
	if (m_SaveCount == SAVE_SPAWN)
	{
		for (int y = 0; y < m_MapBlock.size(); y++)
		{
			for (int x = 0; x < m_MapBlock[y].size(); x++)
			{
				//�@�Z�[�u�p�z��Ɍ��݂̔z���ۑ�
				m_SaveBlock[y][x] = m_MapBlock[y][x];
			}
		}
	}

	//�@�ۑ������f�[�^�ɖ߂�
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_Z))
	{
		for (int y = 0; y < m_MapBlock.size(); y++)
		{
			for (int x = 0; x < m_MapBlock[y].size(); x++)
			{
				m_MapBlock[y][x] = m_SaveBlock[y][x];
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
	//�@�}�E�X�J�[�\���̕\��
	SetMouseDispFlag(true);

	using namespace std;

	OPENFILENAME ofn;							//�@FILENAME�\���̂̒�`
	char path[MAX_PATH] = "";					//�@�t�@�C���p�X��������
	ZeroMemory(&ofn, sizeof(ofn));				//�@�\���̂̃p�X����ɂ���
	ofn.lStructSize = sizeof(OPENFILENAME);		//�@�\���̂̃T�C�Y���w��
	ofn.lpstrFilter = "csv(*.csv)\0*.csv\0"		//�@�g���q�̃t�B���^�[�������� \n�͕��̏I����\��
		"���ׂẴt�@�C��(*.*)\0*.*\0\0";		
	ofn.lpstrFile = path;						//�@�t�@�C���p�X���i�[����|�C���^
	ofn.nMaxFile = MAX_PATH;					//�@lpstrFile�̃o�b�t�@�T�C�Y
	ofn.lpstrDefExt = ".csv";					//�@�g���q���w�肳��Ă��Ȃ����".csv"������
	int result = 0;

	GetSaveFileName(&ofn);

	//�@�t�@�C�����J��
	ofstream ofs(path);

	//�@�P�s�����������玟�̗��
	for (int y = 0; y < m_MapBlock.size(); y++)
	{
		for (int x = 0; x < m_MapBlock[y].size(); x++)
		{
			ofs << m_MapBlock[y][x] << ",";
		}
		ofs << endl;
	}

	//�@�t�@�C�������
	ofs.close();

	//�@�}�E�X�J�[�\���̔�\��
	SetMouseDispFlag(false);
}

//--------------------------------------------------------//
//�Ō�ɏ����o��                                          //
//--------------------------------------------------------//
void PlayScene::LastCheck()
{
	//�@�����o����
	int isSave;

	//�@���b�Z�[�W�{�b�N�X�̕\��
	isSave = MessageBox(
		NULL,
		TEXT("�ۑ����܂����H"),
		TEXT("�m�F"),
		MB_YESNO | MB_ICONQUESTION);

	//�@Yes�Ȃ�Εۑ�����
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}
