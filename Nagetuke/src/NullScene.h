#ifndef NULL_SCENE_H_
#define NULL_SCENE_H_

#include "Scene.h"

class NullScene :
    public Scene
{
public:
    NullScene(SceneManager& sceneManager) :
        Scene{ sceneManager }
    {
    }
    void Start() override {};
    void Update() override {};
    void Draw() const override {};
    void End() override {};
    bool IsSceneEnd() const override { return false; }
    std::string Next() const override { return "NullScene"; }
    void EndScene() override { isSceneEnd_ = true; }
};
#endif//!NULL_SCENE_H_

