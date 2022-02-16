#pragma once
#include "Scene.h"
class NullScene :
    public Scene
{
public:
    void Start() override {};
    void Update() override {};
    void Draw() const override {};
    void End() override {};
    bool IsSceneEnd() const override { return false; }
    std::string Next() const override { return "NullScene"; }
    void EndScene() override { isSceneEnd_ = true; }
};

