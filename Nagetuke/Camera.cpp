#include "Camera.h"
#include "Screen.h"
#include "DxLib.h"
#include "Map.h"
float Camera::x_ = 0;
float Camera::y_ = 0;

void Camera::LookAt(float targetWorldX, float targetWorldY)
{
	x_ = targetWorldX - Screen::Width / 2;
	y_ = targetWorldY - Screen::Height / 2;

	if (x_ < 0) x_ = 0;
	else if (x_ > Map::Width_ * Map::CellSize_ - Screen::Width) x_ = Map::Width_ * Map::CellSize_ - Screen::Width;
	if (y_ < 0) y_ = 0;
	else if (y_ > Map::Height_ * Map::CellSize_ - Screen::Height) y_ = Map::Height_ * Map::CellSize_ - Screen::Height;
}

void Camera::DrawGraph(float worldX, float worldY, int handle, bool flip, float exRate)
{
	DrawRotaGraphF(worldX - x_, worldY - y_, exRate, 0, handle, TRUE, flip);
}

void Camera::DrawLineBox(float left, float top, float right, float bottom)
{
	DrawBoxAA(left - x_, top - y_, right - x_, bottom - y_, GetColor(0, 255, 0), FALSE);
}