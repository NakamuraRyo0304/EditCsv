/*
	ExtendLibInput.h
	DxLibを利用して、入力の状態を管理するクラス。
	DxLibでは、ボタンが押されているか押されていないかは分かるが、
	押された瞬間か、放された瞬間か、というチェックができないため、
	その部分をカバーするための処理をサポートする。


	作成者　：　堀川　和雅
	作成日　：　2021/03/15
*/
#pragma once

class ExtendLibInput
{
private:
	static const int KEY_CODE_MAX;

	int nowJoypadInput;					//	ジョイパッドの現在の入力
	int oldJoypadInput;					//	ジョイパッドの1フレーム前の入力

	int nowKeyInput[256];				//	キーコードの現在の入力
	int oldKeyInput[256];				//	キーコードの1フレーム前の入力

public:
	ExtendLibInput();					//	コンストラクタ
	~ExtendLibInput();					//	デストラクタ

	void Initialize();					//	初期化処理
	void Update();						//	更新処理
	void Finalize();					//	終了処理

	int IsButtonDown(int buttonID);		//	ジョイパッドのボタンが押されているかチェック
	int IsButtonUp(int buttonID);		//	ジョイパッドのボタンが放されているかチェック
	int IsButtonPressed(int buttonID);	//	ジョイパッドのボタンが押された瞬間かチェック
	int IsButtonReleased(int buttonID);	//	ジョイパッドのボタンが放された瞬間かチェック

	int IsKeyDown(int keyCode);			//	キーボードのボタンが押されているかチェック
	int IsKeyUp(int keyCode);			//	キーボードのボタンが放されているかチェック
	int IsKeyPressed(int keyCode);		//	キーボードのボタンが押された瞬間かチェック
	int IsKeyReleased(int keyCode);		//	キーボードのボタンが放された瞬間かチェック
};

