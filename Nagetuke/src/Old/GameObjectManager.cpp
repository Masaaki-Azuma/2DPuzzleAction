#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::‾GameObjectManager()
{
	Clear();
}

void GameObjectManager::Update()
{
	for (auto gameObject : gameObjects_) {
		gameObject->Update();
	}
}

void GameObjectManager::Draw() const
{
	for (auto gameObject : gameObjects_) {
		gameObject->Draw();
	}
}

void GameObjectManager::DrawGUI() const
{
	for (auto gameObject : gameObjects_) {
		gameObject->DrawGUI();
	}
}

void GameObjectManager::Add(GameObject* gameObject)
{
	gameObjects_.push_back(gameObject);
}

void GameObjectManager::Remove()
{
	for (auto itr = gameObjects_.begin(); itr != gameObjects_.end();) {
		if ((*itr)->isDead()) {
			delete* itr;
			itr = gameObjects_.erase(itr);
		}
		else {
			++itr;
		}
	}
}

void GameObjectManager::Clear()
{
	for (auto gameObject : gameObjects_) {
		delete gameObject;
	}
	gameObjects_.clear();
}
