#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <string>
#include "Fade.h"
#include "PlayScene/Map.h"
#include "NullScene.h"

class Scene;

class SceneManager
{
public:
	SceneManager();
	‾SceneManager();

	void Update();
	void Draw();
	void Add(const std::string& name, Scene* scene);
	void Change(std::string name);	//現在のシーンを変更
	void End();					//現在のシーンを終了
	void Clear();				//登録シーンを全て消去

	void SetOverlappingScene(std::string name);	//現在の上乗せシーンを変更

	void StartFade(Fade::State state);
	Map* GetMapPtr() { return &map_; }
	void SetMapLevel(int level);
	void LoadMapNextLevel();
	int GetMapCurrentLevel() const;
	void StartOverlap() { isOverlapping_ = true; }
	void EndOverlap() { isOverlapping_ = false; }
	void EndCurrentScene();

private:
	void DeleteOverlappingScene();			//現在の上乗せシーンを終了
	Scene* currentScene_;
	Scene* currentOverlappingScene_;
	bool isOverlapping_;
	Fade fade_;
	std::unordered_map<std::string, Scene*> scenes_;
	Map map_;

	NullScene nullScene{ *this };

};

#endif//!SCENE_MANAGER_H_

