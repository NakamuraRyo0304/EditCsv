/*
	ExtendLibGraphics.cpp
	DxLibを使用して、少し便利にした機能を実装するクラス。
	元の機能を作成したのは高木先生。

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/

#include <DxLib.h>
#include <math.h>
#include <stdio.h>
#include "ExtendLibGraphics.h"

const int ExtendLibGraphics::NUM_CAPSULE_DIVISION = 16;


//----------------------------------------------------------------------
//! @brief 破線を描画
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int ExtendLibGraphics::DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness)
{
	int vx = x2 - x1;
	int vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = (float)(length * cos(angle));
	float dy = (float)(length * sin(angle));

	int count = (int)(sqrt(vx * vx + vy * vy) / length);

	float x = (float)x1;
	float y = (float)y1;

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLine((int)x, (int)y, (int)(x + dx), (int)(y + dy), color, thickness) == -1)
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLine((int)x, (int)y, x2, y2, color, thickness) == -1)
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 破線を描画(アンチエイリアス効果付き)
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int ExtendLibGraphics::DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = (float)(length * cos(angle));
	float dy = (float)(length * sin(angle));

	int count = (int)(sqrt(vx * vx + vy * vy) / length);

	float x = x1;
	float y = y1;

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLineAA(x, y, (x + dx), (y + dy), color, thickness) == -1)
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLineAA(x, y, x2, y2, color, thickness) == -1)
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief カプセルを描画
//!
//! @param[in] x1        一方の円の中心座標(X座標)
//! @param[in] y1        一方の円の中心座標(Y座標)
//! @param[in] x2        もう一方の円の中心座標(X座標)
//! @param[in] y2        もう一方の円の中心座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int ExtendLibGraphics::DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness)
{
	int vx = x2 - x1;
	int vy = y2 - y1;

	double angle = atan2(vy, vx) + (DX_PI / 2);

	float dx[NUM_CAPSULE_DIVISION + 1];
	float dy[NUM_CAPSULE_DIVISION + 1];
	int i;

	for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
	{
		dx[i] = (float)(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		dy[i] = (float)(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
	}


	if (DrawLine((int)(x1 + dx[0]), (int)(y1 + dy[0]), (int)(x2 + dx[0]), (int)(y2 + dy[0]), color, thickness))
	{
		return -1;
	}

	if (DrawLine((int)(x1 + dx[NUM_CAPSULE_DIVISION]), (int)(y1 + dy[NUM_CAPSULE_DIVISION]), (int)(x2 + dx[NUM_CAPSULE_DIVISION]), (int)(y2 + dy[NUM_CAPSULE_DIVISION]), color, thickness))
	{
		return -1;
	}


	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLine((int)(x1 + dx[i]), (int)(y1 + dy[i]), (int)(x1 + dx[i + 1]), (int)(y1 + dy[i + 1]), color, thickness))
		{
			return -1;
		}
	}

	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLine((int)(x2 - dx[i]), (int)(y2 - dy[i]), (int)(x2 - dx[i + 1]), (int)(y2 - dy[i + 1]), color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief カプセルを描画(アンチエイリアス効果付き)
//!
//! @param[in] x1        一方の円の中心座標(X座標)
//! @param[in] y1        一方の円の中心座標(Y座標)
//! @param[in] x2        もう一方の円の中心座標(X座標)
//! @param[in] y2        もう一方の円の中心座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int ExtendLibGraphics::DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	double angle = atan2(vy, vx) + (DX_PI / 2);

	float dx[NUM_CAPSULE_DIVISION + 1];
	float dy[NUM_CAPSULE_DIVISION + 1];
	int i;

	for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
	{
		dx[i] = (float)(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		dy[i] = (float)(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
	}


	if (DrawLineAA(x1 + dx[0], y1 + dy[0], x2 + dx[0], y2 + dy[0], color, thickness))
	{
		return -1;
	}

	if (DrawLineAA(x1 + dx[NUM_CAPSULE_DIVISION], y1 + dy[NUM_CAPSULE_DIVISION], x2 + dx[NUM_CAPSULE_DIVISION], y2 + dy[NUM_CAPSULE_DIVISION], color, thickness))
	{
		return -1;
	}


	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLineAA(x1 + dx[i], y1 + dy[i], x1 + dx[i + 1], y1 + dy[i + 1], color, thickness))
		{
			return -1;
		}
	}

	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLineAA(x2 - dx[i], y2 - dy[i], x2 - dx[i + 1], y2 - dy[i + 1], color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 透明度付きの資格を描画
//!
//! @param[in] x1        左上の座標(X座標)
//! @param[in] y1        左上の座標(Y座標)
//! @param[in] x2        右下の座標(X座標)
//! @param[in] y2        右下の座標(Y座標)
//! @param[in] color     四角の色
//! @param[in] alpha	 透明度
//----------------------------------------------------------------------
void ExtendLibGraphics::DrawAlphaBox(float x1, float y1, float x2, float y2, unsigned int color, float alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255.0f));
	DrawBoxAA(x1, y1, x2, y2, color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
