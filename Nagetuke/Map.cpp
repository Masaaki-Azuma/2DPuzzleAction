#include "Map.h"
#include <memory>
#include <cassert>
#include "DxLib.h"
#include "Image.h"
#include "Sound.h"
#include "Font.h"
#include "FileReader.h"
#include "Camera.h"
#include "PlayScene.h"
#include "Player.h"
#include "Goal.h"
#include "BoxItem.h"
#include "Game.h"

Map::Map()
{

}

void Map::SpawnObject(int chipX, int chipY, int objectID)
{
	float spawnX = chipX * CellSize_ + CellSize_ * 0.5f;
	float spawnY = chipY * CellSize_ + CellSize_ * 0.5f;

	switch (objectID) {
	case 0:
		playScene_->player_ = std::make_shared<Player>(spawnX, spawnY - 10, playScene_);
		playScene_->gameObjects_.emplace_back(playScene_->player_);
		break;
	case 1:
		playScene_->gameObjects_.emplace_back(std::make_shared<Goal>(spawnX, spawnY, playScene_));
		break;
	case 2:
		playScene_->gameObjects_.emplace_back(std::make_shared<BoxItem>(spawnX, spawnY, playScene_));
		break;
	}
}

void Map::SetLevel(int level)
{
	currentLevel_ = level;
}

void Map::SetNextLevel()
{
	SetLevel(currentLevel_ + 1);
}

void Map::LoadLevel(int levelNum)
{
	playScene_->gameObjects_.clear();
	playScene_->player_.reset();
	//PlaySceneがもつ全オブジェクトをいったん解放
	currentLevel_ = levelNum;
	if (currentLevel_ > MaxLevel_) {
		currentLevel_ = 0;
	}
	std::string stageName = "stage" + std::to_string(currentLevel_);
	LoadTerrain(stageName);
	LoadObjects(stageName);
	Camera::LookAt(playScene_->player_->GetX(), playScene_->player_->GetY());
	Sound::PlayBGM("Assets/BGM/Beat_&#039n&#039_Bass.mp3", 220);
}

void Map::LoadLevel()
{
	//PlaySceneがもつ全オブジェクトをいったん解放
	playScene_->gameObjects_.clear();  //TODO:スマートポインタを廃止するならオブジェクトの解放を明示的に行うこと
	playScene_->player_.reset();

	if (currentLevel_ > MaxLevel_) {
		currentLevel_ = 0;
	}
	std::string stageName = "stage" + std::to_string(currentLevel_);
	LoadTerrain(stageName);
	LoadObjects(stageName);
	Camera::LookAt(playScene_->player_->GetX(), playScene_->player_->GetY());
	Sound::PlayBGM("Assets/BGM/Beat_&#039n&#039_Bass.mp3", 220);
}


//指定したステージを読み込む
void Map::LoadTerrain(std::string stageName)
{
	std::string filePath = "Assets/Map/" + stageName + "_terrain.csv";
	std::vector<std::string> lines = FileReader::ReadLines(filePath);
	assert(lines.size() == Map::Height_);//読み込んだ行数は合っているか？

	for (int y = 0; y < Map::Height_; ++y) {
		std::vector<std::string> splitteds;
		splitteds = FileReader::Split(lines.at(y), ',');
		assert(splitteds.size() == Map::Width_);//読み込んだ列数は合っているか？

		for (int x = 0; x < Map::Width_; ++x) {
			terraine_[x][y] = std::stoi(splitteds.at(x));
		}
	}
}

void Map::LoadNextLevel()
{
	SetNextLevel();
	LoadLevel();
}

void Map::RestartLevel()
{
	LoadLevel(currentLevel_);
}

void Map::LoadObjects(std::string stageName)
{
	std::string filePath = "Assets/Map/" + stageName + "_object.csv";
	std::vector<std::string> lines = FileReader::ReadLines(filePath);
	assert(lines.size() == Map::Height_);//読み込んだ行数は合っているか？

	for (int y = 0; y < Map::Height_; ++y) {
		std::vector<std::string> splitteds;
		splitteds = FileReader::Split(lines.at(y), ',');
		assert(splitteds.size() == Map::Width_);//読み込んだ列数は合っているか？

		for (int x = 0; x < Map::Width_; ++x) {
			int id = std::stoi(splitteds.at(x));
			if (id == -1) continue;
			SpawnObject(x, y, id);
		}
	}
}

//読み込まれているステージを描画する
void Map::DrawTerrain() const
{
	DrawGraph(0, 0, Image::background, TRUE);
	for (int y = 0; y < Map::Height_; y++) {
		for (int x = 0; x < Map::Width_; x++) {
			int id = terraine_[x][y];
			if (id == NONE) continue;
			
			Camera::DrawGraph(
				static_cast<float>(x * CellSize_ + CellSize_ / 2),
				static_cast<float>(y * CellSize_ + CellSize_ / 2),
				Image::mapChip[id], false
			);
		}
	}
}

void Map::DrawGUI() const
{
	static const int fontHandle = Font::fontHandle;
	if (currentLevel_ == 0) {
		DrawStringToHandle(380, 100, "Thank You For Playing!", GetColor(0, 0, 0), fontHandle);
		DrawStringToHandle(220, 200, "Next Stage is Under Construction...", GetColor(0, 0, 0), fontHandle);
		DrawStringToHandle(300, 300, "Press START To Return Title", GetColor(0, 0, 0), fontHandle);
	}
	else {
		DrawFormatStringToHandle(1080, 20, GetColor(0, 0, 0), fontHandle, "Stage %d", currentLevel_);
	}
}

void Map::Draw() const
{
	DrawTerrain();
	DrawGUI();
}

int Map::GetTerrain(float worldX, float worldY) const
{
	if (worldX < 0 || worldY < 0) return NONE;

	//intキャストの切り捨ては、負の値の切り捨てに注意（正負問わず0に近づく）
	int chipX = static_cast<int>(worldX / CellSize_);
	int chipY = static_cast<int>(worldY / CellSize_);

	if (chipX >= Width_ || chipY >= Height_) return NONE;

	//配列にアクセスする場合は必ずインデックス境界チェックをする
	switch (terraine_[chipX][chipY]) {
		//ブロックチップを示すidを列挙
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		return BLOCK;
		break;
	case 20:
	case 21:
	case 22:
	case 23:
		return NEEDLE;
		break;
	default:
		return NONE;
		break;
	}
}

bool Map::IsBlock(float worldX, float worldY) const
{
	return GetTerrain(worldX, worldY) == BLOCK;
}

bool Map::IsNone(float worldX, float worldY) const
{
	return GetTerrain(worldX, worldY) == NONE;
}

bool Map::IsNeedle(float worldX, float worldY) const
{
	return GetTerrain(worldX, worldY) == NEEDLE;
}
