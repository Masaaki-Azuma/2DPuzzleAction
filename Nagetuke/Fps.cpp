#include "Fps.h"

Fps::Fps()
{
	mStartTime = 0;
	mCount = 0;
	mFps = 0;
}

void Fps::Update()
{
	mCount++;
	if (mCount >= N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}

	//game.Update();
	//フレームスキップ処理を書くなら以下

}

void Fps::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void Fps::Wait()
{
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}