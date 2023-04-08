/*
 *	@file	Scene.h
 *	@brief	Sceneの基底クラス
 *	@date	2023-03-03
 *  @human  RyoNakamura
 */
 
#pragma once
#include <DxLib.h>
#include "../../GameDatas/Utility.h"
#include "../../GameDatas/Color.h"
#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"


 //　TODO::変更箇所４:Scene4_IDの追加
enum class SceneID
{
	PlayScene,


	SceneNum
};

class Scene
{
protected:
	GameSystemObjects* pGameSystem = nullptr;
	bool is_ChangeSceneFlag = false;
	bool is_PushSceneChangeFlag = false;

	//	次のシーンを入れる
	SceneID m_nextScene = SceneID::SceneNum;

public:	
	//以下、仮想関数

	virtual ~Scene() = default;

	virtual void Init(int screenWidth, int screenHeight) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;

	virtual void SetGameSystemObject(GameSystemObjects* pObj) = 0;

	virtual bool GetChangeSceneFlag();

public:

	//　通常関数

	//　アプリを落とす関数
	inline void ExitApp() { DxLib_End(); };

	//　Game.cppに次のシーンIDを引き渡す
	SceneID GetNextScene() { return m_nextScene; };

	//　フェード付きのシーン遷移
	void ChangeScene(SceneID nextScene);
};