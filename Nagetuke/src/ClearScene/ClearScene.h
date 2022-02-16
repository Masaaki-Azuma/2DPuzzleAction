#pragma once
#include "Scene.h"

class PlayScene;

class ClearScene :
    public Scene
{
public:
    ClearScene(SceneManager& sceneManager);
    ‾ClearScene();
public:
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override {}
    bool IsSceneEnd() const override;
    std::string Next() const override;
    void EndScene() override { isSceneEnd_ = true; }

private:
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
};

