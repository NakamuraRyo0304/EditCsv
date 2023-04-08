/*
	ExtendLibTime.cpp
	ゲーム内で時間に関する処理を簡略化するためのクラス。
	元の機能を作成したのは高木先生。

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/

#include <DxLib.h>
#include "ExtendLibTime.h"


const int ExtendLibTime::ONE_SECOND = 1000000;


ExtendLibTime::ExtendLibTime() :
	s_frameDeltaTime(0.0f),
	s_frameRate(0.0f),
	previousTime(0),
	currentTime(GetNowHiPerformanceCount()),
	startTime(0),
	frameCount(0)
{

}

ExtendLibTime::~ExtendLibTime()
{

}

// フレームタイマーの更新
void  ExtendLibTime::UpdateFrameTimer()
{
	// 時間の計測
	previousTime = currentTime;
	currentTime = GetNowHiPerformanceCount();


	// フレームの経過時間の更新
	s_frameDeltaTime = (float)(currentTime - previousTime) / ONE_SECOND;


	// 1秒毎にフレームレートの更新
	frameCount++;
	if ((currentTime - startTime) > ONE_SECOND)
	{
		s_frameRate = (float)(frameCount * ONE_SECOND) / (currentTime - startTime);
		startTime = currentTime;
		frameCount = 0;
	}
}

// 直前のフレームからの経過時間の取得
float ExtendLibTime::GetFrameDeltaTime()
{
	return s_frameDeltaTime;
}

// フレームレートの取得
float ExtendLibTime::GetFrameRate()
{
	return s_frameRate;
}
