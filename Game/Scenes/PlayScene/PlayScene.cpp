/*
 *	@file	PlayScene.cpp
 *	@brief  CSVエディタ
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#include <DxLib.h>
#include "PlayScene.h"

//　スクリーンサイズ
#define		SCREEN_WIDTH		1000
#define		SCREEN_HEIGHT		800

//　秒数
#define		SECOND				60
//　フレーム数
#define		FRAME				60
//　60フレーム(1秒) ×　秒数(SECOND)
#define		SAVE_SPAWN			FRAME * SECOND

//　ナンバーの最大値
#define		MAX_NUMBER			10

//　ブロック
#define		BLOCK_SPAWN			20
//　ブロック数
typedef struct { int x, y; }STAGESIZE;
STAGESIZE STAGE_SIZE = { 500,400 };

 //--------------------------------------------------------//
 //コンストラクタ                                          //
 //--------------------------------------------------------//
PlayScene::PlayScene() :
	Scene(),
	m_Mouse(),
	m_BlockNum(),
	m_SaveCount(),
	is_SaveFlag(),
	m_NowColor(),
	m_Move(),
	m_StartPos()
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
	m_Move = { 0 };
	m_StartPos = { 0 };
	m_BlockNum = 0;
	m_SaveCount = 0;

	//　可変長配列の初期化
	std::vector<int>tmp((int)STAGE_SIZE.x, 0);
	m_MapBlock = std::vector < std::vector<int>>((int)STAGE_SIZE.y, tmp);
	m_SaveBlock = m_MapBlock;
}

//--------------------------------------------------------//
//更新処理                                                //
//--------------------------------------------------------//
void PlayScene::Update(float deltaTime)
{
	//　オートセーブ
	AutoSave();

	//　色の変更
	ChangeBlockColor();

	//　マウスの座標取得
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);
	
	//　右クリック描画
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		//　配列範囲外にアクセスしない
		if (m_Mouse.x < 0 || m_Mouse.y < 0) return;

		m_MapBlock[(m_Mouse.y + m_Move.y) / BLOCK_SPAWN][(m_Mouse.x + m_Move.x) / BLOCK_SPAWN] = m_BlockNum;
	}

	//　範囲外に行かないようにする
	m_Mouse.x = Func::Clamp(m_Mouse.x, 0, SCREEN_WIDTH - BLOCK_SPAWN / 2);
	m_Mouse.y = Func::Clamp(m_Mouse.y, 0, SCREEN_HEIGHT - BLOCK_SPAWN / 2);

	//　ホイール回転で数値変更
	m_BlockNum += GetMouseWheelRotVol();
	m_BlockNum = Func::Clamp(m_BlockNum, 0, MAX_NUMBER);

	//　編集が終わったらエンターで終了
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_RETURN))
	{
		//　セーブ確認
		LastExport();
	}

	//　ソフト終了
	if (pGameSystem->GetInputSystem().IsKeyPressed(KEY_INPUT_ESCAPE))
	{
		ExitApp();
	}

	//　マスの移動
	BlockMove();
}

//--------------------------------------------------------//
//描画処理                                                //
//--------------------------------------------------------//
void PlayScene::Draw()
{
	DrawBoxAA(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, White, true);

	// ブロック
	for (int y = 0; y < m_MapBlock.size(); y++)
	{
		for (int x = 0; x < m_MapBlock[y].size(); x++)
		{
			//　数値ありブロック
			switch (m_MapBlock[y][x])
			{
			case 1:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Blue, TRUE);
				break;
			case 2:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Yellow, TRUE);
				break;
			case 3:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Green, TRUE);
				break;
			case 4:
				DrawBox(x * BLOCK_SPAWN + m_Move.x, y * BLOCK_SPAWN + m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN + m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN + m_Move.y,
					Black, TRUE);	
				break;
			case 5:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Red, TRUE);
				break;
			case 6:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Purple, TRUE);
				break;
			case 7:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Orange, TRUE);
				break;
			case 8:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					DeepPink, TRUE);
				break;
			case 9:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Aqua, TRUE);
				break;
			case 10:
				DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
					x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
					Brown, TRUE);
				break;
			}

			//　ボックスの枠
			DrawBox(x * BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN - m_Move.y,
				x * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.x, y * BLOCK_SPAWN + BLOCK_SPAWN - m_Move.y,
				Gray, FALSE);
		}
	}

	//　マウスの位置
	DrawBox(m_Mouse.x - BLOCK_SPAWN / 2 - 1, m_Mouse.y - BLOCK_SPAWN / 2 - 1,
		m_Mouse.x + BLOCK_SPAWN / 2 + 1, m_Mouse.y + BLOCK_SPAWN / 2 + 1,
		Black, true);
	DrawBox(m_Mouse.x - BLOCK_SPAWN / 2, m_Mouse.y - BLOCK_SPAWN / 2,
		m_Mouse.x + BLOCK_SPAWN / 2, m_Mouse.y + BLOCK_SPAWN / 2,
		m_NowColor, true);

	//　デバッグ文字情報
	DebugText();
}

//--------------------------------------------------------//
//終了処理                                                //
//--------------------------------------------------------//
void PlayScene::Finalize()
{
	if (m_MapBlock == m_SaveBlock) return;

	//　最後に書き出すか
	int isSave;

	//　メッセージボックスの表示
	isSave = MessageBox(
		NULL,
		TEXT("変更が保存されていません。\n保存しますか？"),
		TEXT("最終確認"),
		MB_YESNO | MB_ICONQUESTION);

	//　Yesならば保存する
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}

//--------------------------------------------------------//
//デバッグ用文字                                          //
//--------------------------------------------------------//
void PlayScene::DebugText()
{
	//　スクリーン座標
	DrawFormatString(20, 30, Black, "(x,y) = (%d,%d)", m_Mouse.x, m_Mouse.y);
	//　ブロック番号（マウスホイール回転量）
	DrawFormatString(20, 60, Black, "Num = (%d)", m_BlockNum);
	//　セーブまでのカウント
	if ((SAVE_SPAWN - m_SaveCount) / SECOND > 0)
	{
		DrawFormatString(20, 90, Black, "セーブまで:%d", (SAVE_SPAWN - m_SaveCount) / SECOND);
	}

	//　セーブ確認
	if		(m_SaveCount > SAVE_SPAWN + (2 * FRAME))
	{
		DrawFormatString(20, 120, Black, "セーブ中...");
	}
	else if (m_SaveCount > SAVE_SPAWN + (1 * FRAME))
	{
		DrawFormatString(20, 120, Black, "セーブ中..");
	}
	else if (m_SaveCount > SAVE_SPAWN + (0 * FRAME))
	{
		DrawFormatString(20, 120, Black, "セーブ中.");
	}

	DrawFormatString(0, 100, Black, "%d,%d", m_Move.x, m_Move.y);
}

void PlayScene::ChangeBlockColor()
{
	//　ブロックの色変更
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
//マスを移動させる                                        //
//--------------------------------------------------------//
void PlayScene::BlockMove()
{
	GetMousePoint(&m_Mouse.x, &m_Mouse.y);

	m_StartPos = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2};

	if (pGameSystem->GetInputSystem().IsKeyDown(KEY_INPUT_SPACE))
	{
		if (m_StartPos.x > m_Mouse.x)
		{
			if (m_Move.x < 0)return;
			m_Move.x -= 5;
		}
		if (m_StartPos.x < m_Mouse.x)
		{
			m_Move.x += 5;
		}
		if (m_StartPos.y > m_Mouse.y)
		{
			if (m_Move.y < 0)return;
			m_Move.y -= 5;
		}
		if (m_StartPos.y < m_Mouse.y)
		{
			m_Move.y += 5;
		}
	}

	m_Move.x = Func::Clamp(m_Move.x, 0, STAGE_SIZE.x * BLOCK_SPAWN - SCREEN_WIDTH);
	m_Move.y = Func::Clamp(m_Move.y, 0, STAGE_SIZE.y * BLOCK_SPAWN - SCREEN_WIDTH);
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
	if (m_SaveCount > SAVE_SPAWN + 180)
	{
		m_SaveCount = 0;
	}

	//　配列を保存する
	if (m_SaveCount == SAVE_SPAWN)
	{
		for (int y = 0; y < m_MapBlock.size(); y++)
		{
			for (int x = 0; x < m_MapBlock[y].size(); x++)
			{
				//　セーブ用配列に現在の配列を保存
				m_SaveBlock[y][x] = m_MapBlock[y][x];
			}
		}
	}

	//　保存したデータに戻る
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

//　エクスポート用インクルード
#include <fstream>
//--------------------------------------------------------//
//CSVに書き出し                                           //
//--------------------------------------------------------//
void PlayScene::ExportCSV()
{
	//　マウスカーソルの表示
	SetMouseDispFlag(true);

	using namespace std;

	OPENFILENAME ofn;						//FILENAME構造体の定義
	char path[MAX_PATH] = "";				//ファイルパスを初期化
	ZeroMemory(&ofn, sizeof(ofn));			//構造体のパスを空にする
	ofn.lStructSize = sizeof(OPENFILENAME); //構造体のサイズを指定
	ofn.lpstrFilter = "csv(*.csv)\0*.csv\0" //拡張子のフィルターをかける
		"すべてのファイル(*.*)\0*.*\0\0";	
	ofn.lpstrFile = path;					//ファイルパスを格納するポインタ
	ofn.nMaxFile = MAX_PATH;				//lpstrFileのバッファサイズ
	ofn.lpstrDefExt = ".csv";				//拡張子が指定されていなければ".csv"をつける
	int result = 0;

	GetSaveFileName(&ofn);

	//　ファイルを開く
	ofstream ofs(path);

	//　１行書きだしたら次の列へ
	for (int y = 0; y < m_MapBlock.size(); y++)
	{
		for (int x = 0; x < m_MapBlock[y].size(); x++)
		{
			ofs << m_MapBlock[y][x] << ",";
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
	//　書き出すか
	int isSave;

	//　メッセージボックスの表示
	isSave = MessageBox(
		NULL,
		TEXT("保存しますか？"),
		TEXT("確認"),
		MB_YESNO | MB_ICONQUESTION);

	//　Yesならば保存する
	if (isSave == IDYES)
	{
		ExportCSV();
	}
}
