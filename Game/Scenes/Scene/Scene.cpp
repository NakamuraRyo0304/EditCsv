/*
 *	@file	Scene.cpp
 *	@brief	Scene�̊��N���X
 *	@date	2023-02-05
 *  @human  RyoNakamura
 */

#include "Scene.h"

 //--------------------------------------------------------//
 //�V�X�e���̏�����                                        //
 //--------------------------------------------------------//
void Scene::Init(int screenWidth, int screenHeight)
{
	is_ChangeSceneFlag = false;
	is_PushSceneChangeFlag = false;
	pGameSystem = nullptr;
}

//--------------------------------------------------------//
 //�V�[���t���O�̎擾                                      //
 //--------------------------------------------------------//
bool Scene::GetChangeSceneFlag()
{
	return is_ChangeSceneFlag;
}

//--------------------------------------------------------//
//�V�[���؂�ւ�������                                    //
//--------------------------------------------------------//
void Scene::ChangeScene(SceneID nextScene)
{
	//�@�t�F�[�h�C�����I���������s�ł���
	if (is_PushSceneChangeFlag == false)
	{
		m_nextScene = nextScene;
		is_ChangeSceneFlag = true;
	}
}
