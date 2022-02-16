#pragma once
#include "Scene.h"


class TitleScene :
    public Scene
{
private:
    enum State
    {
        START,
        SELECT,
        INCREASE,
        DECREASE
    };
public:
    TitleScene(SceneManager* sceneManager);
    ‾TitleScene();
private:
    void IncreaseLevel();
    void DecreaseLevel();
public:
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override {}
    bool IsSceneEnd() const override;
    virtual std::string Next() const override;
    void EndScene() override { isSceneEnd_ = true; }
private:
    State state_ = START;
    int levelNum_ = 1;
    int levelNameY_ = 500;
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
    SceneManager* sceneManager_{ nullptr };
};

