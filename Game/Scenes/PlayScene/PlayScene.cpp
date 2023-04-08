/*
 *	@file	PlayScene.cpp
 *	@brief  CSVエディタ
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "PlayScene.h"

#define		SCREEN_WIDTH		1000
#define		SCREEN_HEIGHT		800
#define		BLOCK_SPAWN			20

//　秒数
#define		SECOND				60
//　60フレーム(1秒) ×　秒数(SECOND)
#define		SAVE_SPAWN			60 * SECOND

//　ブロック配列
int m_MapBlock[SCREEN_WIDTH / BLOCK_SPAWN][SCREEN_HEIGHT / BLOCK_SPAWN];
int m_SaveBlock[SCREEN_WIDTH / BLOCK_SPAWN][SCREEN_HEIGHT / BLOCK_SPAWN];


 //--------------------------------------------------------//
 //コンストラクタ                                          //
 //--------------------------------------------------------//
PlayScene::PlayScene() :
	Scene(),
	m_Mouse(),
	m_BlockNum(),
	m_SaveCount(),
	is_SaveFlag()
{
	//　マウスカーソルを隠す
	SetMouseDispFlag(false);
}

//--------------------------------------------------------//
//デストラクタ                                            //
//--------------------------------------------------------//
PlayScene::~PlayScene()
{
	InitGraph();

}

//--------------------------------------------------------//
//初期化処理                                              //
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
//更新処理                                                //
//--------------------------------------------------------//
void PlayScene::Update(float deltaTime)
{
	//　オートセーブ
	AutoSave();

	//　マウスの座標取得
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);
	m_Mouse.x = Func::Clamp(m_Mouse.x, 0, SCREEN_WIDTH);
	m_Mouse.y = Func::Clamp(m_Mouse.y, 0, SCREEN_HEIGHT);

	//　右クリック描画
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		m_MapBlock[m_Mouse.x / BLOCK_SPAWN][m_Mouse.y / BLOCK_SPAWN] = m_BlockNum;
	}

	//　ホイール回転で数値変更
	m_BlockNum += GetMouseWheelRotVol();
	m_BlockNum = Func::Clamp(m_BlockNum, 0, 5);

	//　編集が終わったらエンターで終了
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_RETURN))
	{
		//　セーブ確認
		LastExport();
		//　ソフト終了
		ExitApp();
	}
}

//--------------------------------------------------------//
//描画処理                                                //
//--------------------------------------------------------//
void PlayScene::Draw()
{
	DrawBoxAA(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, White, true);

	// ブロック
	for (int y = 0; y < (SCREEN_HEIGHT / BLOCK_SPAWN) + 10; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
		{
			//　数値ありブロック
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

			//　ボックスの枠
			DrawBox(x * BLOCK_SPAWN, y * BLOCK_SPAWN,
				x * BLOCK_SPAWN + BLOCK_SPAWN, y * BLOCK_SPAWN + BLOCK_SPAWN,
				Black, FALSE);
		}
	}

	//　マウスの位置
	DrawBox(m_Mouse.x - BLOCK_SPAWN / 2, m_Mouse.y - BLOCK_SPAWN / 2,
		    m_Mouse.x + BLOCK_SPAWN / 2, m_Mouse.y + BLOCK_SPAWN / 2,
		    Red, true);
	
	//　スクリーン座標
	DrawFormatString(0, 30, Black, "(x,y) = (%d,%d)", m_Mouse.x, m_Mouse.y);
	//　ブロック番号（マウスホイール回転量）
	DrawFormatString(0, 60, Black, "Num = (%d)", m_BlockNum);

	//　セーブ確認
	if (m_SaveCount > SAVE_SPAWN + 60)
	{
		DrawFormatString(0, 120, Black, "セーブ中...");
	}
	else if (m_SaveCount > SAVE_SPAWN + 30)
	{
		DrawFormatString(0, 120, Black, "セーブ中..");
	}
	else if (m_SaveCount > SAVE_SPAWN)
	{
		DrawFormatString(0, 120, Black, "セーブ中.");
	}
}

//--------------------------------------------------------//
//終了処理                                                //
//--------------------------------------------------------//
void PlayScene::Finalize()
{

}

//--------------------------------------------------------//
//10秒に1回セーブする                                     //
//--------------------------------------------------------//
void PlayScene::AutoSave()
{
	//　セーブ中は半透明化
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

	//　保存までカウントダウン
	m_SaveCount++;
	if (m_SaveCount > SAVE_SPAWN + 60)//　1秒だけ確認用に猶予あり
	{
		m_SaveCount = 0;
	}

	//　配列を保存する
	if (m_SaveCount == SAVE_SPAWN)
	{
		for (int y = 0; y < SCREEN_HEIGHT / BLOCK_SPAWN; y++)
		{
			for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
			{
				//　セーブ用配列に現在の配列を保存
				m_SaveBlock[x][y] = m_MapBlock[x][y];
			}
		}
	}

	//　保存したデータに戻る
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

//　エクスポート用インクルード
#include <fstream>
//--------------------------------------------------------//
//CSVに書き出し                                           //
//--------------------------------------------------------//
void PlayScene::ExportCSV()
{
	using namespace std;
		
	//　絶対パス指定
	//string FileName = "C:/Users/it222180/Desktop/Data.csv";
	//　相対パス指定
	string FileName = "Resources/SaveData/Data.csv";

	//　ファイルを開く
	ofstream ofs(FileName);

	//　１行書きだしたら次の列へ
	for (int y = 0; y < SCREEN_HEIGHT / BLOCK_SPAWN; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH / BLOCK_SPAWN; x++)
		{
			ofs << m_MapBlock[x][y] << ",";
		}
		ofs << endl;
	}

	//　ファイルを閉じる
	ofs.close();
}

//--------------------------------------------------------//
//最後に書き出す                                          //
//--------------------------------------------------------//
void PlayScene::LastExport()
{
	//　最後に書き出すか
	int isSave;

	//　メッセージボックスの表示
	isSave = MessageBox(
		NULL,
		TEXT("保存して終わりますか?"),
		TEXT("確認"),
		MB_YESNO | MB_ICONQUESTION);

	//　Yesならば保存する
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}
