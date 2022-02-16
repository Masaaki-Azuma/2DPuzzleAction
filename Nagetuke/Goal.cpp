#include "Goal.h"
#include "DxLib.h"
#include "Camera.h"
#include "Image.h"
#include "PlayScene.h"
#include "Player.h"

Goal::Goal(float x, float y, PlayScene* playScene) :
	GameObject(x, y, playScene, 80, 80),
	Gravity(0.5f),
	vy_(0),
	isFlip_(true)
{
	hitboxOffsetLeft_ = 2;
	hitboxOffsetRight_ = 2;
	hitboxOffsetTop_ = 2;
}

void Goal::Update()
{
	vy_ += Gravity;

	y_ += vy_;
	if (MoveCloseToBottomBlock()) {
		vy_ = 0;
	}

	if (playScene_->player_->GetX() <= x_) isFlip_ = true;
	else								   isFlip_ = false;
}

void Goal::Draw()
{
	Camera::DrawGraph(x_, y_, Image::goal, isFlip_);
}
