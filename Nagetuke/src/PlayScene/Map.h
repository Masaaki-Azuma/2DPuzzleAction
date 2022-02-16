#pragma once
#include <string>
#include <array>

class PlayScene;

class Map
{
public:
	enum State
	{
		NONE = -1,
		BLOCK,
		NEEDLE,
		FLOOR,

	};
private:
	int currentLevel_ = 0;
public:
	static const int MaxLevel_ = 8;
	static const int Width_ = 48;
	static const int Height_ = 24;
	static const int CellSize_ = 64;
	PlayScene* playScene_ = nullptr;
	std::array<std::array<int, Height_>, Width_> terraine_; //array[Width_][Height_]に同義

public:
	Map();
	‾Map() = default;
private:
	void SpawnObject(int chipX, int chipY, int objectID);
public:
	void SetLevel(int level);
	void SetNextLevel();
	void LoadLevel(int levelNum);  //指定レベルをロードする、廃止予定
	void LoadLevel();			   //現在設定されているレベルをロードする、レベルのロードはこちらに統合
	void LoadNextLevel();
	void RestartLevel();
	void LoadTerrain(std::string filePath);
	void LoadObjects(std::string filePath);
	void DrawTerrain() const;
	void DrawGUI() const;
	void Draw() const;
	int GetTerrain(float worldX, float worldY) const;
	int GetCurrentLevel() const { return currentLevel_; }
	bool IsNone(float worldX, float worldY) const;
	bool IsBlock(float worldX, float worldY) const;
	bool IsNeedle(float worldX, float worldY) const;
};

