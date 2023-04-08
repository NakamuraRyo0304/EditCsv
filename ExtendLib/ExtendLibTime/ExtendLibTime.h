/*
	ExtendLibTime.h
	ゲーム内で時間に関する処理を簡略化するためのクラス。

	作成者　：　堀川　和雅
	作成日　：　2021/03/16
*/
#pragma once
#include <windows.h>

class ExtendLibTime
{
private:
	static const int ONE_SECOND;

	float s_frameDeltaTime;					//	 フレームの経過時間[s]
	float s_frameRate;						//	 フレームレート[fps]

	LONGLONG previousTime;                  //	 前回の計測時間
	LONGLONG currentTime;					//	 現在の計測時間
	LONGLONG startTime;						//	 フレームレート計測開始時間
	int      frameCount;					//	 フレーム数


public:
	ExtendLibTime();
	~ExtendLibTime();

	//	フレームタイマーの更新
	void  UpdateFrameTimer();

	//	直前のフレームからの経過時間の取得
	float GetFrameDeltaTime();

	//	フレームレートの取得
	float GetFrameRate();
};

