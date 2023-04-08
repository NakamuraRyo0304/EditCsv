/*
 *	@file	Scene.cpp
 *	@brief	Sceneの基底クラス
 *	@date	2023-02-05
 *  @human  RyoNakamura
 */

#include "Scene.h"

 //--------------------------------------------------------//
 //システムの初期化                                        //
 //--------------------------------------------------------//
void Scene::Init(int screenWidth, int screenHeight)
{
	is_ChangeSceneFlag = false;
	is_PushSceneChangeFlag = false;
	pGameSystem = nullptr;
}

//--------------------------------------------------------//
 //シーンフラグの取得                                      //
 //--------------------------------------------------------//
bool Scene::GetChangeSceneFlag()
{
	return is_ChangeSceneFlag;
}

//--------------------------------------------------------//
//シーン切り替えをする                                    //
//--------------------------------------------------------//
void Scene::ChangeScene(SceneID nextScene)
{
	//　フェードインが終わったら実行できる
	if (is_PushSceneChangeFlag == false)
	{
		m_nextScene = nextScene;
		is_ChangeSceneFlag = true;
	}
}
