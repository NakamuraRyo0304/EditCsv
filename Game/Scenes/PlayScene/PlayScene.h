/*
 *	@file	PlayScene.h
 *	@brief  CSVエディタ
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#pragma once

#include "../Scene/Scene.h"

//　ポジション型の宣言
typedef struct { int x, y; }Position;

class PlayScene : public Scene
{
private:
	//　マウスの位置
	Position m_Mouse;

	//　CSVに書き出す数値
	int m_BlockNum;

	//　セーブ用変数
	int m_SaveCount;
	bool is_SaveFlag;

	//　現在の色
	unsigned int m_NowColor;

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

	//　オートセーブ
	void AutoSave();

	//　CSVに書き出し
	void ExportCSV();

	//　終了時に呼び出す
	void LastExport();
};
