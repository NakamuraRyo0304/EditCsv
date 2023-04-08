/*
	ExtendLibInput.cpp
	DxLibを利用して、入力の状態を管理するクラス。
	DxLibでは、ボタンが押されているか押されていないかは分かるが、
	押された瞬間か、放された瞬間か、というチェックができないため、
	その部分をカバーするための処理をサポートするため、実際の処理を記述する。


	作成者　：　堀川　和雅
	作成日　：　2021/03/15
*/
#include <DxLib.h>
#include "ExtendLibInput.h"

const int ExtendLibInput::KEY_CODE_MAX = 256;

//	コンストラクタ
ExtendLibInput::ExtendLibInput()
{
	//	変数の初期化を行う
	Initialize();
}

//	デストラクタ
ExtendLibInput::~ExtendLibInput()
{

}


//	初期化処理
void ExtendLibInput::Initialize()
{
	//	ジョイパッドのボタン情報用変数の初期化
	nowJoypadInput = 0;
	oldJoypadInput = 0;

	for (int i = 0; i < KEY_CODE_MAX; i++)
	{
		//	キーボードのボタン情報用変数の初期化
		nowKeyInput[i] = 0;
		oldKeyInput[i] = 0;
	}

}

//	更新処理
void ExtendLibInput::Update()
{
	//	変数oldJoypadInputに変数nowJoypadInputを入れ、1フレーム前の情報を確保する
	oldJoypadInput = nowJoypadInput;

	//	ループでoldKeyInput[i]の中にnowKeyInput[i]を入れ、1フレーム前の情報を確保する
	for (int i = 0; i < KEY_CODE_MAX; i ++)
	{
		oldKeyInput[i] = nowKeyInput[i];
	}

	//	ジョイパッドのボタン情報を更新する
	nowJoypadInput = GetJoypadInputState(DX_INPUT_PAD1);

	//	キーボードのボタン情報をループで更新する
	for (int i = 0; i < KEY_CODE_MAX; i++)
	{
		nowKeyInput[i] = CheckHitKey(i);
	}
}

//	終了処理
void ExtendLibInput::Finalize()
{
	//	何か必要な終了処理があれば、行う
}


//	ジョイパッドのボタンが押されているかチェック
int ExtendLibInput::IsButtonDown(int buttonID)
{
	//	指定されたボタンIDが押されている状態かチェックする
	if ((nowJoypadInput & buttonID) != 0)
	{
		return 1;
	}

	return 0;
}

//	ジョイパッドのボタンが放されているかチェック
int ExtendLibInput::IsButtonUp(int buttonID)
{
	//	指定されたボタンIDが放されている状態かチェックする
	if ((nowJoypadInput & buttonID) == 0)
	{
		return 1;
	}

	return 0;
}

//	ジョイパッドのボタンが押された瞬間かチェック
int ExtendLibInput::IsButtonPressed(int buttonID)
{
	//	指定されたボタンIDが、前フレームで押されておらず、今フレームで押されていたら、1を返す
	if ((nowJoypadInput & buttonID) == 1 &&
		(oldJoypadInput & buttonID) == 0)
	{
		return 1;
	}

	return 0;
}

//	ジョイパッドのボタンが放された瞬間かチェック
int ExtendLibInput::IsButtonReleased(int buttonID)
{
	//	指定されたボタンIDが、前フレームで押されており、今フレームで押されていなかったら、1を返す
	if ((nowJoypadInput & buttonID) == 0 &&
		(oldJoypadInput & buttonID) == 1)
	{
		return 1;
	}


	return 0;
}

//	キーボードのボタンが押されているかチェック
int ExtendLibInput::IsKeyDown(int keyCode)
{
	//	指定されたキーコードが押されている状態かチェックする
	if (nowKeyInput[keyCode] == 1)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが放されているかチェック
int ExtendLibInput::IsKeyUp(int keyCode)
{
	//	指定されたキーコードが放されている状態かチェックする
	if (nowKeyInput[keyCode] == 0)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが押された瞬間かチェック
int ExtendLibInput::IsKeyPressed(int keyCode)
{
	//	指定されたキーコードが、前フレームで押されておらず、今フレームで押されていたら、1を返す
	if (oldKeyInput[keyCode] == 0 &&
		nowKeyInput[keyCode] == 1)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが放された瞬間かチェック
int ExtendLibInput::IsKeyReleased(int keyCode)
{
	//	指定されたキーコードが、前フレームで押されており、今フレームで押されていなかったら、1を返す
	if (oldKeyInput[keyCode] == 1 &&
		nowKeyInput[keyCode] == 0)
	{
		return 1;
	}

	return 0;
}



