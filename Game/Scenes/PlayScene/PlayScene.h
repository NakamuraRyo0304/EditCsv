/*
 *	@file	PlayScene.h
 *	@brief  CSV�G�f�B�^
 *	@date	2023-04-07
 *  @human  RyoNakamura
 */

#pragma once

#include "../Scene/Scene.h"
#include <vector>

//�@�|�W�V�����^�̐錾
typedef struct Position
{
	// ���W
	int x, y;

	// �R���X�g���N�^
	Position(int a = 0, int b = 0) { x = a, y = b; }

	// ���Z�q�̃I�[�o�[���[�h
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
	//�@�}�E�X�̈ʒu
	Position m_Mouse;
	Position m_Move;
	Position m_Start;
	Position m_End;

	//�@��ʒ��S�ʒu
	Position m_CenterPos;

	//�@UI�t���O
	bool is_UiFlag;

	//�@CSV�ɏ����o�����l
	int m_BlockNum;

	//�@�Z�[�u�p�ϐ�
	int m_SaveCount;
	bool is_SaveFlag;

	//�@���݂̐F
	unsigned int m_NowColor;

	//�@�u���b�N�z��
	std::vector<std::vector<int>> m_MapBlock;
	std::vector<std::vector<int>> m_SaveBlock;
	//�@�u���b�N�̑傫��
	int m_BlockSize;

public:
	PlayScene();
	~PlayScene();

	void Init(int screenWidth, int screenHeight) override;
	void Update(float deltaTime)override;
	void Draw()override;
	void Finalize()override;

	//�@�C���v�b�g�V�X�e���̃Z�b�g
	void SetGameSystemObject(GameSystemObjects* pObj)override
	{
		pGameSystem = pObj;
	};

	//�@�V�[���J��
	bool GetChangeSceneFlag() override
	{
		return is_ChangeSceneFlag;
	};

	//�@�f�o�b�O����
	void DebugText();

	//�@�u���b�N�F�ύX
	void ChangeBlockColor();

	//�@�}�X���ړ�������
	void BlockMove();

	//�@�I�[�g�Z�[�u
	void AutoSave();

	//�@CSV�ɏ����o��
	void ExportCSV();

	//�@�I�����ɌĂяo��
	void LastCheck();

	//�@UI��\������
	void DrawUserInterface();

	//�@�l�p�`�̓h��Ԃ�
	void SquareBox();
};
