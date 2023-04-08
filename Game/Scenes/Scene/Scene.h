/*
 *	@file	Scene.h
 *	@brief	Scene�̊��N���X
 *	@date	2023-03-03
 *  @human  RyoNakamura
 */
 
#pragma once
#include <DxLib.h>
#include "../../GameDatas/Utility.h"
#include "../../GameDatas/Color.h"
#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"


 //�@TODO::�ύX�ӏ��S:Scene4_ID�̒ǉ�
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

	//	���̃V�[��������
	SceneID m_nextScene = SceneID::SceneNum;

public:	
	//�ȉ��A���z�֐�

	virtual ~Scene() = default;

	virtual void Init(int screenWidth, int screenHeight) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;

	virtual void SetGameSystemObject(GameSystemObjects* pObj) = 0;

	virtual bool GetChangeSceneFlag();

public:

	//�@�ʏ�֐�

	//�@�A�v���𗎂Ƃ��֐�
	inline void ExitApp() { DxLib_End(); };

	//�@Game.cpp�Ɏ��̃V�[��ID�������n��
	SceneID GetNextScene() { return m_nextScene; };

	//�@�t�F�[�h�t���̃V�[���J��
	void ChangeScene(SceneID nextScene);
};