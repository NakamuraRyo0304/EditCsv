/*
 *	@file	Game.cpp
 *	@brief	シーン切り替えを主にするクラス
 *	@date	2023-03-04
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "Game.h"


//--------------------------------------------------------//
//コンストラクタ                                          //
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
	//　m_sceneIDと同じシーンを記述
	m_nowScene = new PlayScene();
}

//--------------------------------------------------------//
//デストラクタ                                            //
//--------------------------------------------------------//
Game::~Game()
{
	//　ポインタの削除
	delete m_nowScene;
	m_nowScene = nullptr;
}


//--------------------------------------------------------//
//初期化処理                                              //
//--------------------------------------------------------//
void Game::Init()
{
	m_nowScene->Init(screenWidth,screenHeight);
}

//--------------------------------------------------------//
//更新処理                                                //
//--------------------------------------------------------//
void Game::Update()
{
	bool is_ChangeSceneFlag = false;

	//　デルタタイムの計算
	CalDelta();

	m_nowScene->Update(deltaTime);
	is_ChangeSceneFlag = m_nowScene->GetChangeSceneFlag();

	//　シーン変更のタイミング
	if(is_ChangeSceneFlag)
	{
		//　シーンの新規作成
		NewScene();
	}
}

//--------------------------------------------------------//
//描画処理                                                //
//--------------------------------------------------------//
void Game::Draw()
{
	//　シーンが入っていなければ早期リターン
	if (m_nowScene == nullptr) return;

	m_nowScene->Draw();
}

//--------------------------------------------------------//
//終了処理                                                 //
//--------------------------------------------------------//
void Game::Finalize()
{
	m_nowScene->Finalize();
}

//--------------------------------------------------------//
//deltaTimeの計算                                         //
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
//スクリーンサイズ指定                                    //
//--------------------------------------------------------//
void Game::SetScreenSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

//--------------------------------------------------------//
//インプットシステムの設定                                //
//--------------------------------------------------------//
void Game::SetGameSystemObject(GameSystemObjects* pObj)
{
	pGameSystem = pObj;
	m_nowScene->SetGameSystemObject(pGameSystem);
}

//--------------------------------------------------------//
//シーンの新規作成                                        //
//--------------------------------------------------------//
void Game::NewScene()
{

	//・・・・・・・・・ここから削除処理・・・・・・・・・//

	if (m_nowScene == nullptr)
	{
		return;
	}
	else
	{
		//　次のシーンを保存してから削除処理をする
		m_sceneID = m_nowScene->GetNextScene();
		m_nowScene->Finalize();

		//　シーンの削除をする
		delete m_nowScene;
		m_nowScene = nullptr;
	}

	//・・・・・・・・・ここから作成処理・・・・・・・・・//

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
