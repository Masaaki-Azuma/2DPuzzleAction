#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>
#include "ThrownBox.h"
#include "Direction.h"

class Player :
    public GameObject
{
private:
    enum State
    {
        WALKING,
        JUMPING,
    };
private:
    const float MovingSpeed_;
    const float MaxFallSpeed_;
    const int MaxThrowInteval_;
    const float Gravity_;
    unsigned int availableBox_;
    float vx_;
    float vy_;
    int throwInterval_;
    bool canThrow_;
    bool isFlip_;
    int deadCounter;
    bool isDrawn_;
    Direction direction_;
    State state_;
    std::vector<std::shared_ptr<ThrownBox>> boxes_;
public:
    Player(float x, float y, PlayScene* playScene);
    ‾Player();
private:
    void HandleInput();
    void MoveX();
    void MoveY();
    void FreeFall();
    void ThrowBox();
    void GatherBox();
    bool IsBox(float x, float y);
    void CheckNeedle();
    void DrawCross();
    void DrawBoxGui();
    void Die();
    //bool IsBlock(float worldX, float worldY);
    //bool IsNeedle(float worldX, float worldY);
public:
    void OnCollision(GameObject& other) override;
    void Update() override;
    void Draw() override;
    void ArrangeBoxes();
};

