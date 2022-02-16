#include "GameObject.h"
#include "DxLib.h"
#include "PlayScene/Camera.h" 
#include "PlayScene/PlayScene.h"
#include "PlayScene/Map.h"

GameObject::GameObject(float x, float y, PlayScene* playScene, int width, int height) :
	x_(x),
	y_(y),
	prevX_(x),
	prevY_(y),
	playScene_(playScene),
	imageWidth_(width),
	imageHeight_(height),
	hitboxOffsetLeft_(0),
	hitboxOffsetRight_(0),
	hitboxOffsetTop_(0),
	hitboxOffsetBottom_(0),
	isDead_(false)
{
	//オフセットは必要に応じてサブクラスコンストラクタで行う
}

/// <summary>
/// 右ブロックとの当たり判定を行い、めり込まないよう位置を修正する
/// </summary>
/// <returns>当たったらtrue、追加の処理は戻り値を呼出元が受け取って行う</returns>
bool GameObject::MoveCloseToRightBlock()
{
	float right = GetRight();
	float top = GetTop() + 1;
	float middle = y_;
	float bottom = GetBottom() - 1;

	const int CellSize = Map::CellSize_;

	bool isBlock =
		IsBlock(right, top)    ||
		IsBlock(right, middle) ||
		IsBlock(right, bottom);

	bool isNeedle =
		IsNeedle(right, top) ||
		IsNeedle(right, middle) ||
		IsNeedle(right, bottom);

	if (isBlock || isNeedle) {
		int chipX = static_cast<int>(right / CellSize);//TODO:右辺が含まれるチップ
		float blockleft = static_cast<float>(chipX * CellSize - 1);
		SetRight(blockleft);
		return true;
	}
	return false;
}

/// <summary>
/// 左ブロックとの当たり判定を行い、めり込まないよう位置を修正する
/// </summary>
/// <returns>当たったらtrue、追加の処理は戻り値を呼出元が受け取って行う</returns>
bool GameObject::MoveCloseToLeftBlock()
{
	float left = GetLeft();
	float top = GetTop() + 1;
	float middle = y_;
	float bottom = GetBottom() - 1;

	const int CellSize = Map::CellSize_;

	bool isBlock =
		IsBlock(left, top)    ||
		IsBlock(left, middle) ||
		IsBlock(left, bottom);

	bool isNeedle =
		IsNeedle(left, top) ||
		IsNeedle(left, middle) ||
		IsNeedle(left, bottom);

	if (isBlock || isNeedle) {
		int chipX = static_cast<int>(left / CellSize) + 1;//TODO:左辺が含まれるチップ
		float blockRight = static_cast<float>(chipX * CellSize);
		SetLeft(blockRight);
		return true;
	}
	return false;
}

/// <summary>
/// 上ブロックとの当たり判定を行い、めり込まないよう位置を修正する
/// </summary>
/// <returns>当たったらtrue、追加の処理は戻り値を呼出元が受け取って行う</returns>
bool GameObject::MoveCloseToAboveBlock()
{
	float left = GetLeft() + 0.1f;
	float right = GetRight() + 0.1f;
	float top = GetTop();

	const int CellSize = Map::CellSize_;

	bool isBlock =
		IsBlock(left, top) ||
		IsBlock(right, top);
	bool isNeedle =
		IsNeedle(left, top) ||
		IsNeedle(right, top);

	if (isBlock || isNeedle)
	{
		int chipY = static_cast<int>(top / CellSize) + 1;
		float blockBottom = static_cast<float>(chipY * CellSize);//小数の剰余を出すのが面倒なのでこっち
		SetTop(blockBottom);
		return true;
	}
	return false;
}

/// <summary>
/// 下ブロックとの当たり判定を行い、めり込まないよう位置を修正する
/// </summary>
/// <returns>当たったらtrue、追加の処理は戻り値を呼出元が受け取って行う</returns>
bool GameObject::MoveCloseToBottomBlock()
{
	float left = GetLeft() + 0.1f;
	float right = GetRight() - 0.1f;
	float bottom = GetBottom();

	const int CellSize = Map::CellSize_;

	bool isBlock =
		IsBlock(left, bottom) ||
		IsBlock(right, bottom);
	bool isNeedle =
		IsNeedle(left, bottom) ||
		IsNeedle(right, bottom);

	if (isBlock || isNeedle) {
		int chipY = static_cast<int>(bottom / CellSize);
		float blockTop = static_cast<float>(chipY * CellSize - 0.1f);
		SetBottom(blockTop);
		return true;
	}
	return false;
}
bool GameObject::IsBlock(float worldX, float worldY)
{
	return playScene_->IsBlock(worldX, worldY);
}

bool GameObject::IsNeedle(float worldX, float worldY)
{
	return playScene_->IsNeedle(worldX, worldY);
}

float GameObject::GetLeft() const
{
	return x_ - imageWidth_ / 2 + hitboxOffsetLeft_;
}

float GameObject::GetRight() const
{
	return x_ + imageWidth_ / 2 - hitboxOffsetRight_;
}

float GameObject::GetTop() const
{
	return y_ - imageHeight_ / 2 + hitboxOffsetTop_;
}

float GameObject::GetBottom() const
{
	return y_ + imageHeight_ / 2 - hitboxOffsetBottom_;
}

float GameObject::GetPrevLeft() const
{
	return prevX_ - imageWidth_ / 2 + hitboxOffsetLeft_;
}

float GameObject::GetPrevRight() const
{
	return prevX_ + imageWidth_ / 2 - hitboxOffsetRight_;
}

float GameObject::GetPrevTop() const
{
	return prevY_ - imageHeight_ / 2 + hitboxOffsetTop_;
}

float GameObject::GetPrevBottom() const
{
	return prevY_ + imageHeight_ / 2 - hitboxOffsetBottom_;
}

void GameObject::StorePrevState()
{
	prevX_ = x_;
	prevY_ = y_;
}

void GameObject::SetLeft(float left)
{
	x_ = left - hitboxOffsetLeft_ + imageWidth_ / 2;
}

void GameObject::SetRight(float right)
{
	x_ = right + hitboxOffsetRight_ - imageWidth_ / 2;
}

void GameObject::SetTop(float top)
{
	y_ = top - hitboxOffsetTop_ + imageHeight_ / 2;
}

void GameObject::SetBottom(float bottom)
{
	y_ = bottom + hitboxOffsetBottom_ - imageHeight_ / 2;
}

void GameObject::DrawHitBox()
{
	Camera::DrawLineBox(GetLeft(), GetTop(), GetRight(), GetBottom());
}
