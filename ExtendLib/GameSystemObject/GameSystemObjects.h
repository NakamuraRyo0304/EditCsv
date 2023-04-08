/*
	GameSystemObjects.h
	ゲームで使う基本的な機能のオブジェクトを集めたクラス。

	作成者　：　堀川　和雅
	作成日　：　2021/03/15
*/
#pragma once
#include "../ExtendLibInput/ExtendLibInput.h"
#include "../ExtendLibTime/ExtendLibTime.h"

class GameSystemObjects
{
private:
	ExtendLibInput* pInputSystem;
	ExtendLibTime* pTimerObject;
	bool isInitialize;

public:
	GameSystemObjects();					//	コンストラクタ
	~GameSystemObjects();					//	デストラクタ

	void Initialize();						//	初期化処理
	void Update();							//	更新処理
	void Render();							//	描画処理
	void Finalize();						//	終了処理

	ExtendLibInput& GetInputSystem();		//	インプット処理用クラスオブジェクトの取得
	ExtendLibTime& GetTimerSystem();		//	タイマー処理用クラスオブジェクトの取得
	bool GetInitializeFlag();				//	初期化済みかを示すフラグの内容を取得する
};