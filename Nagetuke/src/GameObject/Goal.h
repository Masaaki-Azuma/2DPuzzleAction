#pragma once
#include "GameObject.h"

class PlayScene;

class Goal :
    public GameObject
{
private:
    const float Gravity;
    float vy_;
    bool isFlip_;
public:
    Goal(float x, float y, PlayScene* playScene);
public:
    void Update() override;
    void Draw() override;
    void OnCollision(GameObject& other){}
};

