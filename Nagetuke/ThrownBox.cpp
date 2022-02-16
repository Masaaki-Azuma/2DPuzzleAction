#include "ThrownBox.h"
#include "DxLib.h"
#include "Image.h"
#include "Sound.h"
#include "Camera.h"
#include "Screen.h"
#include "Player.h"
#include <typeinfo>

ThrownBox::ThrownBox(float x, float y, PlayScene* playScene, Direction direction):
	GameObject(x, y, playScene, 64, 64),
	MoveSpeed_(15),
	vx_(0),
	vy_(0),
	state_(Flying)
{
	switch (direction) {
	case RIGHT:
		vx_ = MoveSpeed_;
		break;
	case LEFT:
		vx_ = -MoveSpeed_;
		break;
	case UP:
		vy_ = -MoveSpeed_;
		break;
	case DOWN:
		vy_ = MoveSpeed_;
		break;
	}
	Sound::PlaySE(Sound::boxThrow);
}

ThrownBox::‾ThrownBox()
{
}

void ThrownBox::Move()
{
	if (state_ == Sticking) return;
	x_ += vx_;
	y_ += vy_;

	bool isSticking = false;
	if (vx_ < 0) isSticking = MoveCloseToLeftBlock();
	else if (vx_ > 0) isSticking = MoveCloseToRightBlock();
	else if (vy_ < 0) isSticking = MoveCloseToAboveBlock();
	else if (vy_ > 0) {
		isSticking = MoveCloseToBottomBlock();
	}

	if (isSticking) ChangeState(Sticking);

	if (state_ == Flying) {
		float right = x_ + imageWidth_ / 2 - Camera::GetX();
		float left = x_ - imageWidth_ / 2 - Camera::GetX();
		float bottom = y_ + imageHeight_ / 2 - Camera::GetY();
		float top = y_ - imageHeight_ / 2 - Camera::GetY();
		if (right < 0 ||
			left > Screen::Width ||
			bottom < 0 ||
			top > Screen::Height) {
			isDead_ = true;
		}
	}
	
}

void ThrownBox::ChangeState(State state)
{
	switch (state) {
	case Sticking:
		state_ = Sticking;
		vx_ = 0;
		vy_ = 0;
		Sound::PlaySE(Sound::stickBlock);
	}
}

void ThrownBox::OnCollision(GameObject& other)
{
	//ラッピングしたくない？
	if (typeid(other).name() == typeid(ThrownBox).name()) {
		if (this->state_ == Sticking) return;
		state_ = Sticking;

		if      (vx_ > 0) SetRight (other.GetLeft());
		else if (vx_ < 0) SetLeft  (other.GetRight());
		else if (vy_ > 0) SetBottom(other.GetTop());
		else if (vy_ < 0) SetTop   (other.GetBottom());
	}
	/*else if (タイプ比較) {

	}
	*/
}

void ThrownBox::Update()
{
	Move();
}

void ThrownBox::Draw()
{
	Camera::DrawGraph(x_, y_, Image::thrownBox, false);
}
