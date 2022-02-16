#include "Player.h"
#include "DxLib.h"
#include "Util/Input.h"
#include "AssetsManager/Image.h"
#include "AssetsManager/Sound.h"
#include "PlayScene/Camera.h"
#include "PlayScene/PlayScene.h"
#include "PlayScene/Map.h"
#include <typeinfo>
#include "Util/MyMath.h"
#include "Goal.h"
#include "Game.h"
#include "Effect/CrossEffect.h"
#include "BoxItem.h"


Player::Player(float x, float y, PlayScene* playScene) :
	GameObject(x, y, playScene, 80, 80),
	MovingSpeed_(5),
	MaxFallSpeed_(10),
	MaxThrowInteval_(20),
	Gravity_(0.45f),
	availableBox_(0),
	vx_(0),
	vy_(0),
	throwInterval_(0),
	canThrow_(true),
	isFlip_(false),
	deadCounter(0),
	isDrawn_(true),
	direction_(RIGHT),
	state_(WALKING)
{
	hitboxOffsetLeft_ = 9;
	hitboxOffsetRight_ = 9;
	hitboxOffsetTop_ = 8;
}

Player::‾Player()
{
}

void Player::HandleInput()
{
	if (Input::GetButton(PAD_INPUT_LEFT)) {//←
		vx_ = -MovingSpeed_;
		direction_ = LEFT;
		isFlip_ = true;
	}
	else if (Input::GetButton(PAD_INPUT_RIGHT)) {//→
		vx_ = MovingSpeed_;
		direction_ = RIGHT;
		isFlip_ = false;
	}
	else if (Input::GetButton(PAD_INPUT_UP)) {//↑
		vx_ = 0;
		direction_ = UP;
	}
	else if (Input::GetButton(PAD_INPUT_DOWN)) {//↓
		vx_ = 0;
		direction_ = DOWN;
	}
	else {
		vx_ = 0;
	}

	if (state_ != JUMPING && Input::GetButtonDown(PAD_INPUT_A)) {//A
		vy_ = -9.0f;
		state_ = JUMPING;
		Sound::PlaySE(Sound::jump);
	}

	if (Input::GetButtonDown(PAD_INPUT_Y)) {//L
		ThrowBox();
	}

	if (Input::GetButtonDown(PAD_INPUT_Z)) {//R
		GatherBox();
	}
}

void Player::MoveX()
{
	x_ += vx_;


	if (GetLeft() < 0) SetLeft(0);
	else if (GetRight() > Map::Width_ * Map::CellSize_) SetRight(Map::Width_ * Map::CellSize_);

	if (GetTop() > Map::Height_ * (Map::CellSize_ + 1)) {
		Die();
	}

	CheckNeedle();

	MoveCloseToLeftBlock();
	MoveCloseToRightBlock();
}

void Player::MoveY()
{
	y_ += vy_;

	CheckNeedle();

	bool isGrounded = false;
	if (MoveCloseToAboveBlock()) {
		vy_ = 0;
	}
	if (MoveCloseToBottomBlock()) {
		vy_ = 0;
		isGrounded = true;			//直接state_をいじっても良い？（state_実際に変える処理は一カ所にまとめて書いた方が見やすい気はする）
	}

	if (isGrounded) state_ = WALKING;
	else			state_ = JUMPING;
}

void Player::FreeFall()
{
	vy_ += Gravity_;
	if (vy_ > MaxFallSpeed_) vy_ = MaxFallSpeed_;
}

void Player::ThrowBox()
{
	if (boxes_.size() < availableBox_ && throwInterval_ <= 0) {
		throwInterval_ = MaxThrowInteval_;

		float spawnX = x_;
		float spawnY = y_ + 8;
		const float dif = 70;
		const float shootableLength = 20;
		switch (direction_) {
		case RIGHT:
			spawnX += dif;
			if (IsBlock(spawnX + shootableLength, spawnY)) canThrow_ = false;
			if (IsNeedle(spawnX + shootableLength, spawnY)) canThrow_ = false;
			if (IsBox(spawnX + shootableLength, spawnY)) canThrow_ = false;
			break;
		case LEFT:
			spawnX -=dif;
			if (IsBlock(spawnX - shootableLength, spawnY)) canThrow_ = false;
			if (IsNeedle(spawnX - shootableLength, spawnY)) canThrow_ = false;
			if (IsBox(spawnX - shootableLength, spawnY)) canThrow_ = false;
			break;
		case UP:
			spawnY -= dif;
			if (IsBlock(spawnX, spawnY - shootableLength - 8)) canThrow_ = false;
			if (IsNeedle(spawnX, spawnY - shootableLength - 8)) canThrow_ = false;
			if (IsBox(spawnX, spawnY - shootableLength)) canThrow_ = false;
			break;
		case DOWN:
			spawnY += dif;
			if (IsBlock(spawnX, spawnY + shootableLength)) canThrow_ = false;
			if (IsNeedle(spawnX, spawnY + shootableLength)) canThrow_ = false;
			if (IsBox(spawnX, spawnY)) canThrow_ = false;
			break;
		}

		if (!canThrow_) {
			playScene_->effects_.emplace_back(std::make_unique<CrossEffect>(spawnX, spawnY));
			return;
		}

		auto tb = std::make_shared<ThrownBox>(static_cast<int>(spawnX), static_cast<int>(spawnY), playScene_, direction_);
		playScene_->gameObjects_.emplace_back(tb);//vector<GameObject>
		boxes_.emplace_back(tb);//vector<ThrownBox>
	}
}

void Player::GatherBox()
{
	bool gathered = false;
	for (auto& b : boxes_) {
		b->isDead_ = true;
		gathered = true;
	}
	if (gathered) {
		Sound::PlaySE(Sound::gather);
	}

}

bool Player::IsBox(float x, float y)
{
	for (auto& tb : boxes_) {
		const int boxSize = 30;
		bool isBox = MyMath::RectRectIntersect(x - boxSize, x + boxSize, y - boxSize, y + boxSize,
			tb->GetLeft(), tb->GetRight(), tb->GetTop(), tb->GetBottom());
		if (isBox) return true;
	}
	
	return false;
}

void Player::CheckNeedle()
{
	float left = GetLeft();
	float right = GetRight();
	float top = GetTop();
	float middle = y_;
	float bottom = GetBottom();

	if (IsNeedle(left, top) ||
		IsNeedle(left, middle) ||
		IsNeedle(left, bottom) ||
		IsNeedle(right, top) ||
		IsNeedle(right, middle) ||
		IsNeedle(right, bottom)) {
		Die();
	}
}

void Player::DrawCross()
{
	const int dif = 80;
	switch (direction_) {
	case RIGHT:
		Camera::DrawGraph(x_ + dif, y_, Image::cross, false);
		break;
	case LEFT:
		Camera::DrawGraph(x_ - dif, y_, Image::cross, false);
		break;
	case UP:
		Camera::DrawGraph(x_, y_ - dif, Image::cross, false);
		break;
	case DOWN:
		Camera::DrawGraph(x_, y_ + dif, Image::cross, false);
		break;
	}
}

void Player::DrawBoxGui()
{
	int remainingBox = availableBox_ - boxes_.size();
	for (int i = 0; i < availableBox_; i++) {
		if (i < remainingBox) {
			DrawGraph(20 + 40 * i, 20, Image::boxItem, true);
		}
		else {
			DrawGraph(20 + 40 * i, 20, Image::boxItemBlank, true);
		}
	}
}

void Player::Die()
{
	isDrawn_ = false;
	Sound::PlaySE(Sound::death);
	deadCounter = 50;
}

//bool Player::IsBlock(float worldX, float worldY)
//{
//	return playScene_->IsBlock(worldX, worldY);
//}
//
//bool Player::IsNeedle(float worldX, float worldY)
//{
//	return playScene_->IsNeedle(worldX, worldY);
//}


void Player::OnCollision(GameObject& other)
{
	auto otherName = typeid(other).name();
	if (otherName == typeid(ThrownBox).name()) {
		auto tb = dynamic_cast<ThrownBox*>(&other);
		if (tb->GetState() == ThrownBox::Flying) return;
		bool prevHitX = this->GetPrevLeft() < other.GetRight() && this->GetPrevRight() > other.GetLeft();
		bool prevHitY = this->GetPrevTop() < other.GetBottom() - 0.1f && this->GetPrevBottom() > other.GetTop() + 0.1f;
		//ここの入れ子どうにかなりませんか？
		if (prevHitX) {//上下から当たったら
			if (vy_ < 0) {
				SetTop(other.GetBottom());
				vy_ = 0;
			}
			else if (vy_ > 0) {
				SetBottom(other.GetTop());
				vy_ = 0;
				state_ = WALKING;
			}
		}
		else if (prevHitY) {//左右から当たったら
			if (vx_ > 0) SetRight(other.GetLeft());
			else if (vx_ < 0) SetLeft(other.GetRight());
		}
	}
	else if (otherName == typeid(Goal).name()) {
		//クリア処理を書く
		playScene_->GameClear();
	}
	else if (otherName == typeid(BoxItem).name()) {
		availableBox_++;
		Sound::PlaySE(Sound::getItem);
	}
}

void Player::Update()
{
	if (deadCounter > 0) {
		deadCounter--;
		if (deadCounter <= 0) {
			playScene_->RestartLevel();
			isDead_ = true;
		}
		return;
	}
	throwInterval_--;
	if (throwInterval_ <= 0) canThrow_ = true;
	StorePrevState();
	HandleInput();
	FreeFall();
	MoveX();
	MoveY();
}

void Player::Draw()
{
	if (!isDrawn_) return;

	Camera::DrawGraph(x_, y_, Image::player[0], isFlip_);

	DrawBoxGui();
}

void Player::ArrangeBoxes()//boxes_から死んだハコを削除
{
	auto result = std::remove_if(boxes_.begin(), boxes_.end(), [](auto& b) {return b->isDead_; });
	boxes_.erase(result, boxes_.end());
}
