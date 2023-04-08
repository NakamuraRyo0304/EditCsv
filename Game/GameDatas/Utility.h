#pragma once
/*
 *	@file	Utility.h
 *	@brief	����@�\�̃N���X
 *	@date	2022-12-23
 *  @human  RyoNakamura
 */

#include <math.h>
#include <random>
#include <time.h>

namespace Func
{
	//--------------------------------------------------------//
	//Clamp�֐�                                               //
	//@brief                                                  //
	//�u�Ώےl�A�ŏ��l�A�ő�l�v����͂���ƁA                //
	// �ŏ��l����ő�l�܂łŐ��䂷��                         //
	//--------------------------------------------------------//

	//�@�ΏہA�ŏ��A�ő�
	inline int Clamp(int v, int min, int max)
	{
		if (v < min) return min;
		if (v > max) return max;

		return v;
	}

	//--------------------------------------------------------//
	//Lerp�֐�                                                //
	//@brief                                                  //
	//�u�ŏ��l�A�ő�l�A���x�v����͂���ƁA                  //
	// �ŏ��l����ő�l�܂ł̊Ԃ̒l���Ԃ���                 //
	//--------------------------------------------------------//

	//�@�ŏ��A�ő�A���x
	inline float Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	
	//--------------------------------------------------------//
	//Oblique�֐�                                             //
	//@brief                                                  //
	//�u���A��A�E�A���v�̏��ɍ��W����͂���ƁA              //
	// ���̐����̒��������߂�@�@�@                           //
	//--------------------------------------------------------//

	//�@���A��A�E�A���̍��W
	inline float Oblique(float w1, float h1, float w2, float h2)
	{
		double l, dx, dy;

		dx = (double)w2 - w1;

		dy = (double)h2 - h1;

		l = sqrt(dx * dx + dy * dy);

		return (float)l;
	}

	//--------------------------------------------------------//
	//Random �֐�                                             //
	//@brief                                                  //
	//�ŏ��l�Ɣ͈͂���͂���Ƃ��͈̔͂��烉���_���Œl��Ԃ�  //
	//--------------------------------------------------------//

	//�@�ŏ��A�͈�
	inline int Random(int min, int range)
	{
		int number;

		srand(unsigned int(time(NULL)));

		number = rand() % range + min;

		return number;
	}
}