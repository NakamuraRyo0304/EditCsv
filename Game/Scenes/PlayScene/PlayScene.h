/*
 *	@file	PlayScene.h
 *	@brief  CSVエディタ
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#pragma once

#include "../Scene/Scene.h"

class PlayScene : public Scene
{
private:
	typedef struct { int x, y; }Position;
	Position m_Mouse;
	int m_BlockNum;
	int m_SaveCount;
	bool is_SaveFlag;

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

	//　オートセーブ
	void AutoSave();

	//　CSVに書き出し
	void ExportCSV();

	//　終了時に呼び出す
	void LastExport();
};
