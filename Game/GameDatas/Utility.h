#pragma once
/*
 *	@file	Utility.h
 *	@brief	多種機能のクラス
 *	@date	2022-12-23
 *  @human  RyoNakamura
 */

#include <math.h>
#include <random>
#include <time.h>

namespace Func
{
	//--------------------------------------------------------//
	//Clamp関数                                               //
	//@brief                                                  //
	//「対象値、最小値、最大値」を入力すると、                //
	// 最小値から最大値までで制御する                         //
	//--------------------------------------------------------//

	//　対象、最小、最大
	inline int Clamp(int v, int min, int max)
	{
		if (v < min) return min;
		if (v > max) return max;

		return v;
	}

	//--------------------------------------------------------//
	//Lerp関数                                                //
	//@brief                                                  //
	//「最小値、最大値、速度」を入力すると、                  //
	// 最小値から最大値までの間の値を補間する                 //
	//--------------------------------------------------------//

	//　最小、最大、速度
	inline float Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	
	//--------------------------------------------------------//
	//Oblique関数                                             //
	//@brief                                                  //
	//「左、上、右、下」の順に座標を入力すると、              //
	// その線分の長さを求める　　　                           //
	//--------------------------------------------------------//

	//　左、上、右、下の座標
	inline float Oblique(float w1, float h1, float w2, float h2)
	{
		double l, dx, dy;

		dx = (double)w2 - w1;

		dy = (double)h2 - h1;

		l = sqrt(dx * dx + dy * dy);

		return (float)l;
	}

	//--------------------------------------------------------//
	//Random 関数                                             //
	//@brief                                                  //
	//最小値と範囲を入力するとその範囲からランダムで値を返す  //
	//--------------------------------------------------------//

	//　最小、範囲
	inline int Random(int min, int range)
	{
		int number;

		srand(unsigned int(time(NULL)));

		number = rand() % range + min;

		return number;
	}
}