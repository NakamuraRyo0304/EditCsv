/*
	ExtendLibMath.h
	計算を行う際に便利となる機能を実装するクラス。

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/
#pragma once
#include <minwindef.h>


class ExtendLibMath
{
private:


public:
	ExtendLibMath();
	~ExtendLibMath();

	// [度]から[ラジアン]への単位変換
	float ToRadians(float degree);
	// [ラジアン]から[度]への単位変換
	float ToDegrees(float radian);
	// 指定した値を下限～上限の範囲内に収める(int版)
	int   ClampI(int   x, int   min, int   max);
	// 指定した値を下限～上限の範囲内に収める(float版)
	float ClampF(float x, float min, float max);
	// 浮動小数点数型の誤差を考慮に入れた比較
	BOOL FloatEquals(float a, float b);

};
