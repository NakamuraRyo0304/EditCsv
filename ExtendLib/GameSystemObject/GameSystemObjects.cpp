/*
	GameSystemObjects.cpp
	ゲームで使う基本的な機能のオブジェクトを集めたクラス。

	作成者　：　堀川　和雅
	作成日　：　2021/03/15
*/
#include "GameSystemObjects.h"

//	コンストラクタ
GameSystemObjects::GameSystemObjects() :
	pInputSystem(nullptr),
	isInitialize(false)
{

}

//	デストラクタ
GameSystemObjects::~GameSystemObjects()
{
	pInputSystem = nullptr;
}

//	初期化処理
void GameSystemObjects::Initialize()
{
	pInputSystem = new ExtendLibInput();
	pInputSystem->Initialize();

	pTimerObject = new ExtendLibTime();

	isInitialize = true;
}

//	更新処理
void GameSystemObjects::Update()
{
	if (!isInitialize)
	{
		//	初期化されていなければ、更新処理をしない
		return;
	}

	//	ボタンシステムの更新を行う
	pTimerObject->UpdateFrameTimer();
	pInputSystem->Update();
}

//	描画処理
void GameSystemObjects::Render()
{

}

//	終了処理
void GameSystemObjects::Finalize()
{
	delete pTimerObject;
	pTimerObject = nullptr;
	delete pInputSystem;
	pInputSystem = nullptr;
}


//	インプット処理用クラスオブジェクトの取得
ExtendLibInput& GameSystemObjects::GetInputSystem()
{
	return (*pInputSystem);
}

//	タイマー処理用クラスオブジェクトの取得
ExtendLibTime& GameSystemObjects::GetTimerSystem()
{
	return (*pTimerObject);
}

//	初期化済みかを示すフラグの内容を取得する
bool GameSystemObjects::GetInitializeFlag()
{
	return isInitialize;
}
