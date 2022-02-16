#pragma once
#include "GameObject.h"
#include "Direction.h"

class PlayScene;

class ThrownBox :
    public GameObject
{
public:
    enum State
    {
        Flying,
        Sticking
    };
private:
    const float MoveSpeed_;
    float vx_;
    float vy_;
public:
    State state_;
public:
    ThrownBox(float x, float y, PlayScene* playScene, Direction direction);
    ‾ThrownBox();
private:
    void Move();
    void ChangeState(State state);
public:
    State GetState() const { return state_; }
    void OnCollision(GameObject& other) override;
    void Update() override;
    void Draw() override;

};

