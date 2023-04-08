/*
 *	@file	WinMain.cpp
 *	@brief	プログラムのエントリーポイントと、
            ゲームのメインループを定義するファイル。
 *	@date	2021-03-15
 *  @human  KazuoHorikawa
 *  @rfact  RyoNakamura
 */

//	DxLibエンジンを使うために必要なインクルード
#include <DxLib.h>

//	Gameクラスを使用するために必要なインクルード
#include "Game/Game.h"

#include "ExtendLib/MemoryLeakDetector.h"
#include "ExtendLib/GameSystemObject/GameSystemObjects.h"

//　アイコン変更
#include"Resources/Icon/Icon.h"

//画面サイズ
#define SCREEN_WIDTH						1000
#define SCREEN_HEIGHT						800


//	ウィンドウタイトルに表示する文字
#define GAME_TITLE							"Edit"


//　ここから処理がスタート
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
			       LPSTR lpCmdLine, int nShowCmd)
{
	//	未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nShowCmd);

	// ウインドウタイトルの設定
	SetMainWindowText(GAME_TITLE);  

#if defined(_DEBUG)

	//	メモリーリーク検出機構のセットアップ
	SetUpMemoryLeakDetector();

#endif
	
	//	デバッグ情報用ログファイルは出力しない
	SetOutApplicationLogValidFlag(FALSE);	

	//	起動モードの設定
	ChangeWindowMode(TRUE);					//	ウインドウモードで実行

	//	初期状態の画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	//　ウィンドウの位置を設定
	SetWindowPosition(350, 30);

	//　アイコンの変更
	SetWindowIconID(ICON_ID);

	//	DXライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		//　エラー処理
		return -1;
	}

	//	画面の描画先を設定
	SetDrawScreen(DX_SCREEN_BACK);			

	//	メインループ内で使用する変数を宣言する
	GameSystemObjects systemObject;

	//	ゲームの処理を実際に記述しているクラスオブジェクト
	Game gameJobObject;						

	//	宣言した変数の初期化が必要であれば、以下で行う

	systemObject.Initialize();

	gameJobObject.SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameJobObject.SetGameSystemObject(&systemObject);

	//	ゲームの処理を行う前に、初期化処理を行う
	gameJobObject.Init();				

	//	メインループ。
	//	ESCキーが押されたら終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	ここにプログラムを書いていく
		// --------------------------------------------------------------------------

		//　更新処理。
		systemObject.Update();
		gameJobObject.Update();

		//	描画処理。
		//	画面を初期化&描画処理の開始
		ClearDrawScreen();

		systemObject.Render();
		gameJobObject.Draw();

		//	裏画面の内容を表画面に反映させる&描画処理の終了
		ScreenFlip();

		//	フレーム内の処理終了！
		// --------------------------------------------------------------------------
	}

	//	プログラムを終了する前に、ゲームの終了処理を行う
	gameJobObject.Finalize();				

	systemObject.Finalize();

	InitGraph();

	//	DXライブラリの終了処理
	if (DxLib_End() == -1)
	{
		//　エラー処理
		return -1;
	}

	//	正常終了
	return 0;	
}
