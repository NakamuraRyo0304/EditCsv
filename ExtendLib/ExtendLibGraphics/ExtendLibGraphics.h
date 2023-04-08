/*
	ExtendLibGraphics.h
	DxLibを使用して、少し便利にした機能を実装するクラス

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/

#pragma once


class ExtendLibGraphics
{
private:
	static const int NUM_CAPSULE_DIVISION;

public:
	ExtendLibGraphics();
	~ExtendLibGraphics();

	// 破線を描画
	int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness = 1);
	// 破線を描画(アンチエイリアス効果付き)
	int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness = 1.0f);
	// カプセルを描画
	int DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness = 1);
	// カプセルを描画(アンチエイリアス効果付き)
	int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness = 1.0f);
	// 透明度付きの資格を描画
	void DrawAlphaBox(float x1, float y1, float x2, float y2, unsigned int color, float alpha);


};