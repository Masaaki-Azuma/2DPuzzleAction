#include "BoxItem.h"
#include "DxLib.h"
#include <cmath>
#include <typeinfo>
#include "PlayScene/Camera.h"
#include "AssetsManager/Image.h"
#include "Player.h"

BoxItem::BoxItem(float x, float y, PlayScene* playScene):
	GameObject(x, y, playScene, 64, 64),
	centerX_(x),
	centerY_(y),
	theta(0)
{
}

void BoxItem::OnCollision(GameObject& other)
{
	auto otherName = typeid(other).name();
	if (otherName == typeid(Player).name()) {
		isDead_ = true;
	}
}

void BoxItem::Update()
{
	theta += 0.02f;
	y_ = centerY_ + std::sinf(theta) * 20;
}

void BoxItem::Draw()
{
	Camera::DrawGraph(x_, y_, Image::bubble, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	Camera::DrawGraph(x_, y_, Image::boxItem, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
