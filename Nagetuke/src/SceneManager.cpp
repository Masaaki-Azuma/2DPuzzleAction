#include "SceneManager.h"


SceneManager::SceneManager():
	currentScene_{&nullScene},
	currentOverlappingScene_{&nullScene},
	isOverlapping_{false}
{
}

SceneManager::‾SceneManager()
{
	Clear();
}

void SceneManager::Update()
{

	fade_.Update();

	if (fade_.IsStoppping()) {
		fade_.Reset();
	}
	else if (fade_.IsRunning()) {
		return;
	}
	//フェード中これより下の処理を実行しない

	if (isOverlapping_) {
		currentOverlappingScene_->Update();
	}
	else {
		currentScene_->Update();
	}

	if (!isOverlapping_) DeleteOverlappingScene();
	if (currentScene_->IsSceneEnd()) {
		Change(currentScene_->Next());
	}
}

void SceneManager::Draw()
{
	currentScene_->Draw();
	if (currentOverlappingScene_) {
		currentOverlappingScene_->Draw();
	}

	fade_.Draw();
}

void SceneManager::Add(const std::string& name, Scene* scene)
{
	scenes_[name] = scene;
}

void SceneManager::Change(std::string name)
{
	End();
	currentScene_ = scenes_[name];
	currentScene_->Start();
}

void SceneManager::End()
{
	DeleteOverlappingScene();
	currentScene_->End();
	currentScene_ = &nullScene;
}

void SceneManager::Clear()
{
	End();
	for (auto& pair : scenes_) {
		delete pair.second;
	}
	scenes_.clear();
}

void SceneManager::SetOverlappingScene(std::string name)
{
	StartOverlap();
	currentOverlappingScene_ = scenes_[name];
	currentOverlappingScene_->Start();
}

void SceneManager::DeleteOverlappingScene()
{
	EndOverlap();
	currentOverlappingScene_->End();
	currentOverlappingScene_ = &nullScene;
}

void SceneManager::StartFade(Fade::State state)
{
	fade_.Start(state);
}

void SceneManager::SetMapLevel(int level)
{
	map_.SetLevel(level);
}

void SceneManager::LoadMapNextLevel()
{
	map_.LoadNextLevel();
}

int SceneManager::GetMapCurrentLevel() const
{
	return map_.GetCurrentLevel();
}

void SceneManager::EndCurrentScene()
{
	currentScene_->EndScene();
}
