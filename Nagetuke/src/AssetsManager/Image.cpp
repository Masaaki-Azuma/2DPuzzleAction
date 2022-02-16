#include "AssetsManager/Image.h"
#include"DxLib.h"

int Image::background;
int Image::black;

int Image::mapChip[24];
int Image::player[8];
int Image::thrownBox;
int Image::boxItem;
int Image::boxItemBlank;
int Image::bubble;
int Image::goal;
int Image::cross;

int Image::clearLogo;

int Image::titleLogo;
int Image::cover;

void Image::Load()
{
	background = LoadGraph("Assets/Image/backGround.png");
	black = LoadGraph("Assets/Image/fadeoutBlack.png");

	LoadDivGraph("Assets/Image/mapChip.png", 24, 4, 6, 64, 64, mapChip);
	LoadDivGraph("Assets/Image/player.png", 8, 4, 2, 80, 80, player);
	thrownBox = LoadGraph("Assets/Image/thrownBox.png");
	boxItem = LoadGraph("Assets/Image/boxItem.png");
	boxItemBlank = LoadGraph("Assets/Image/boxItemBlank.png");
	bubble = LoadGraph("Assets/Image/bubble.png");
	goal = LoadGraph("Assets/Image/goal.png");
	cross = LoadGraph("Assets/Image/cross.png");

	clearLogo = LoadGraph("Assets/Image/clearLogo.png");

	titleLogo = LoadGraph("Assets/Image/titleLogo.png");
	cover = LoadGraph("Assets/Image/cover_100_200.png");
}

void Image::Delete()
{
	InitGraph();
}
