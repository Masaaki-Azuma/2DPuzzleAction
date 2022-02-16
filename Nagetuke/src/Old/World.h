#ifndef WORLD_H_
#define WORLD_H_

#include "GameObjectManager.h"
#include "PlayScene/Camera.h"

class World
{
public:
	void Update();
	void Draw();
private:
	GameObjectManager gameObjectManager_;
	Camera camera_;
};
#endif//!WORLD_H_
