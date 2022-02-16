#pragma once
#include "GameObject.h"

class PlayScene;

class BoxItem :
    public GameObject
{
private:
    float centerX_;
    float centerY_;
    float theta;
public:
    BoxItem(float x, float y, PlayScene* playScene);
public:
    void OnCollision(GameObject& other) override;
    void Update() override;
    void Draw() override;
};

