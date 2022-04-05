#pragma once
#include "Effect.h"
class CrossEffect :
    public Effect
{
public:
    CrossEffect(float x, float y);
public:
    void Update() override;
    void Draw() override;
};

