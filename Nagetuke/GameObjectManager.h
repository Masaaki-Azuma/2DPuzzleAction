#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <vector>

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager() = default;
	‾GameObjectManager();
	void Update();
	void Draw() const;
	void DrawGUI() const;
	void Add(GameObject* gameObject);
	void Remove();
	void Clear();
private:
	std::vector<GameObject*> gameObjects_;
};
#endif//!GAME_OBJECT_MANAGER_H_

