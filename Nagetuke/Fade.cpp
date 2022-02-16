#include "Fade.h"
#include "DxLib.h"
#include "Image.h"

Fade::Fade():
	alpha_(0),
	state_(WAIT)
{
}

void Fade::FadeIn()
{
	alpha_ -= 10;
	if (alpha_ < 0) {
		alpha_ = 0;
		state_ = STOP;
	}
}

void Fade::FadeOut()
{
	alpha_ += 10;
	if (alpha_ > 255) {
		alpha_ = 255;
		state_ = STOP;
	}
}

void Fade::Update()
{
	if (state_ == WAIT) return;

	if (state_ == FADEIN) {
		FadeIn();
	}
	else if (state_ == FADEOUT) {
		FadeOut();
	}
}

void Fade::Draw()
{
	if (state_ == WAIT) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawGraph(0, 0, Image::black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Fade::Start(State state)
{
	if (state == FADEIN) {
		alpha_ = 255;
		state_ = state;
	}
	else if (state == FADEOUT) {
		alpha_ = 0;
		state_ = state;
	}
}

bool Fade::IsWaiting()
{
	return state_ == WAIT;
}

bool Fade::IsStoppping()
{
	return state_ == STOP;
}

bool Fade::IsRunning()
{
	return !IsWaiting();
}

void Fade::Reset()
{
	state_ = WAIT;
}
