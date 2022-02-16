#include "World.h"

void World::Update()
{
	gameObjectManager_.Update();
	gameObjectManager_.Remove();
}

void World::Draw()
{
	gameObjectManager_.Draw();
}
