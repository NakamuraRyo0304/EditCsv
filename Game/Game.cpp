/*
 *	@file	Game.cpp
 *	@brief	�V�[���؂�ւ�����ɂ���N���X
 *	@date	2023-03-04
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "Game.h"


//--------------------------------------------------------//
//�R���X�g���N�^                                          //
//--------------------------------------------------------//
Game::Game() :
	pGameSystem(nullptr),
	screenWidth(0),
	screenHeight(0),
	oldTime((LONGLONG)0),
	nowTime((LONGLONG)0),
	deltaTime(0.0f),
	firstWait(false),
	m_sceneID(SceneID::PlayScene)
{
	//�@m_sceneID�Ɠ����V�[�����L�q
	m_nowScene = new PlayScene();
}

//--------------------------------------------------------//
//�f�X�g���N�^                                            //
//--------------------------------------------------------//
Game::~Game()
{
	//�@�|�C���^�̍폜
	delete m_nowScene;
	m_nowScene = nullptr;
}


//--------------------------------------------------------//
//����������                                              //
//--------------------------------------------------------//
void Game::Init()
{
	m_nowScene->Init(screenWidth,screenHeight);
}

//--------------------------------------------------------//
//�X�V����                                                //
//--------------------------------------------------------//
void Game::Update()
{
	bool is_ChangeSceneFlag = false;

	//�@�f���^�^�C���̌v�Z
	CalDelta();

	m_nowScene->Update(deltaTime);
	is_ChangeSceneFlag = m_nowScene->GetChangeSceneFlag();

	//�@�V�[���ύX�̃^�C�~���O
	if(is_ChangeSceneFlag)
	{
		//�@�V�[���̐V�K�쐬
		NewScene();
	}
}

//--------------------------------------------------------//
//�`�揈��                                                //
//--------------------------------------------------------//
void Game::Draw()
{
	//�@�V�[���������Ă��Ȃ���Α������^�[��
	if (m_nowScene == nullptr) return;

	m_nowScene->Draw();
}

//--------------------------------------------------------//
//�I������                                                 //
//--------------------------------------------------------//
void Game::Finalize()
{
	m_nowScene->Finalize();
}

//--------------------------------------------------------//
//deltaTime�̌v�Z                                         //
//--------------------------------------------------------//
void Game::CalDelta()
{
	oldTime = nowTime;
	nowTime = GetNowHiPerformanceCount();

	deltaTime = (float)((nowTime - oldTime) / 1000000.0f);

	if (!firstWait && deltaTime < 1.0f)
	{
		firstWait = true;
	}
	else if (!firstWait)
	{
		return;
	}
}

//--------------------------------------------------------//
//�X�N���[���T�C�Y�w��                                    //
//--------------------------------------------------------//
void Game::SetScreenSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

//--------------------------------------------------------//
//�C���v�b�g�V�X�e���̐ݒ�                                //
//--------------------------------------------------------//
void Game::SetGameSystemObject(GameSystemObjects* pObj)
{
	pGameSystem = pObj;
	m_nowScene->SetGameSystemObject(pGameSystem);
}

//--------------------------------------------------------//
//�V�[���̐V�K�쐬                                        //
//--------------------------------------------------------//
void Game::NewScene()
{

	//�E�E�E�E�E�E�E�E�E��������폜�����E�E�E�E�E�E�E�E�E//

	if (m_nowScene == nullptr)
	{
		return;
	}
	else
	{
		//�@���̃V�[����ۑ����Ă���폜����������
		m_sceneID = m_nowScene->GetNextScene();
		m_nowScene->Finalize();

		//�@�V�[���̍폜������
		delete m_nowScene;
		m_nowScene = nullptr;
	}

	//�E�E�E�E�E�E�E�E�E��������쐬�����E�E�E�E�E�E�E�E�E//

	switch (m_sceneID)
	{
	case SceneID::PlayScene:
		m_nowScene = new PlayScene();
		break;
	default:
		break;
	}

	m_nowScene->Init(screenWidth, screenHeight);
	m_nowScene->SetGameSystemObject(pGameSystem);
}
