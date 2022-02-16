#ifndef PAUSE_SCENE_H_
#define PAUSE_SCENE_H_

#include "Scene.h"

class PauseScene :
    public Scene
{
public:
    PauseScene(SceneManager& sceneManager);
    ‾PauseScene();
public:
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override;
    bool IsSceneEnd() const override;
    void EndScene() override { isSceneEnd_ = true; }
    std::string Next() const override;
private:
    int selectedOption_ = 0;
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
};
#endif//!PAUSE_SCENE_H_
