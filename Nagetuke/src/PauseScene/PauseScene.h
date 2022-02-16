#pragma once
#include "Scene.h"
class PauseScene :
    public Scene
{
    enum Option
    {
        RETURN, //0
        TITLE,
    };
public:
    PauseScene(SceneManager& sceneManager);
    ‾PauseScene();
public:
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override {}
    bool IsSceneEnd() const override;
    void EndScene() override { isSceneEnd_ = true; }
    std::string Next() const override;
private:
    int selectedOption_ = 0;
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
};

