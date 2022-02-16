#pragma once
#include "Scene.h"
#include <vector>
#include <memory>

class Map;
class Player;
class GameObject;
class Effect;

class PlayScene :
    public Scene
{
public:
    std::shared_ptr<Player> player_;
    std::vector<std::shared_ptr<GameObject>> gameObjects_;//ポインタによる動的ポリモーフィズム
    std::vector<std::unique_ptr<Effect>> effects_;

public:
    PlayScene(SceneManager* sceneManager);
    ‾PlayScene();
public:
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override;
    bool IsSceneEnd() const override;
    void EndScene() override { isSceneEnd_ = true; }
    std::string Next() const override;
    void RestartLevel();
    Map* GetMapPtr() { return map_; }
    bool IsBlock(float x, float y);
    bool IsNeedle(float x, float y);
    void GameClear();
private:
    Map* map_ = nullptr;
    bool isLevelEnd_ = false;
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
    SceneManager* sceneManager_{ nullptr };
};

