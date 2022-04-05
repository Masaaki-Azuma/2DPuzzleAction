#include "CrossEffect.h"
#include "DxLib.h"
#include "PlayScene/Camera.h"
#include "AssetsManager/Image.h"
#include "AssetsManager/Sound.h"

CrossEffect::CrossEffect(float x, float y)
{
	x_ = x;
	y_ = y;
	isDead_ = false;
	timer_ = 20;
	Sound::PlaySE(Sound::beep);
}

void CrossEffect::Update()
{
	timer_--;
	if (timer_ <= 0) Die();
}

void CrossEffect::Draw()
{
	Camera::DrawGraph(x_, y_, Image::cross, false);
}
