/*
 *	@file	PlayScene.h
 *	@brief  CSVエディタ
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#pragma once

#include "../Scene/Scene.h"
#include <vector>

//　ポジション型の宣言
typedef struct Position
{
	// 座標
	int x, y;

	// コンストラクタ
	Position(int a = 0, int b = 0) { x = a, y = b; }

	// 演算子のオーバーロード
	bool operator==(const Position& name) const
	{
		return ((x == name.x) && (y == name.y));
	}
	bool operator!=(const Position& name) const
	{
		return ((x != name.x) or (y != name.y));
	}
	Position operator+(const Position& name) const
	{
		return Position(x + name.x, y + name.y);
	}
};

class PlayScene : public Scene
{
private:
	//　マウスの位置
	Position m_Mouse;
	Position m_Move;
	Position m_Start;
	Position m_End;

	//　画面中心位置
	Position m_CenterPos;

	//　UIフラグ
	bool is_UiFlag;

	//　CSVに書き出す数値
	int m_BlockNum;

	//　セーブ用変数
	int m_SaveCount;
	bool is_SaveFlag;

	//　現在の色
	unsigned int m_NowColor;

	//　ブロック配列
	std::vector<std::vector<int>> m_MapBlock;
	std::vector<std::vector<int>> m_SaveBlock;
	//　ブロックの大きさ
	int m_BlockSize;

public:
	PlayScene();
	~PlayScene();

	void Init(int screenWidth, int screenHeight) override;
	void Update(float deltaTime)override;
	void Draw()override;
	void Finalize()override;

	//　インプットシステムのセット
	void SetGameSystemObject(GameSystemObjects* pObj)override
	{
		pGameSystem = pObj;
	};

	//　シーン遷移
	bool GetChangeSceneFlag() override
	{
		return is_ChangeSceneFlag;
	};

	//　デバッグ文字
	void DebugText();

	//　ブロック色変更
	void ChangeBlockColor();

	//　マスを移動させる
	void BlockMove();

	//　オートセーブ
	void AutoSave();

	//　CSVに書き出し
	void ExportCSV();

	//　終了時に呼び出す
	void LastCheck();

	//　UIを表示する
	void DrawUserInterface();

	//　四角形の塗りつぶし
	void SquareBox();
};
