/*
	ExtendLibMath.cpp
	計算を行う際に便利となる機能を実装するクラス。
	元の機能を作成したのは高木先生。

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/

#include <float.h>
#include <math.h>
#include <DxLib.h>
#include "ExtendLibMath.h"


ExtendLibMath::ExtendLibMath()
{

}

ExtendLibMath::~ExtendLibMath()
{

}



//----------------------------------------------------------------------
//! @brief 角度の単位変換([度]→[ラジアン])
//!
//! @param[in] degree 角度[度]
//!
//! @return 角度[ラジアン]
//----------------------------------------------------------------------
float ExtendLibMath::ToRadians(float degree)
{
	return degree * DX_PI_F / 180.0f;
}



//----------------------------------------------------------------------
//! @brief 角度の単位変換([ラジアン]→[度])
//!
//! @param[in] radian 角度[ラジアン]
//!
//! @return 角度[度]
//----------------------------------------------------------------------
float ExtendLibMath::ToDegrees(float radian)
{
	return radian * 180.0f / DX_PI_F;
}



//----------------------------------------------------------------------
//! @brief 指定した値を下限～上限の範囲内に収める(int版)
//!
//! @param[in] x   範囲内に収めたい値の現在値
//! @param[in] min 下限
//! @param[in] max 上限
//!
//! @return 下限～上限の範囲内に収めた値
//----------------------------------------------------------------------
int ExtendLibMath::ClampI(int x, int min, int max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}



//----------------------------------------------------------------------
//! @brief 指定した値を、下限～上限の範囲内に収める(float版)
//!
//! @param[in] x   範囲内に収めたい値の現在値 
//! @param[in] min 下限
//! @param[in] max 上限
//!
//! @return 下限～上限の範囲内に収めた値
//----------------------------------------------------------------------
float ExtendLibMath::ClampF(float x, float min, float max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}



//----------------------------------------------------------------------
//! @brief 浮動小数点数型の誤差を考慮に入れた比較
//!
//! @param[in] a 比較対象の値
//! @param[in] b 比較対象の値
//!
//! @retval TRUE  誤差が指定範囲(FLT_EPSILON)以内の場合
//! @retval FALSE それ以外の場合
//----------------------------------------------------------------------
BOOL ExtendLibMath::FloatEquals(float a, float b)
{
	if (fabsf(a - b) < FLT_EPSILON)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




