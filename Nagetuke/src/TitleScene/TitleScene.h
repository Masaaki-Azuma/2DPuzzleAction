#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "Scene.h"

class TitleScene :
    public Scene
{
private:
    //画面状態
    enum State
    {
        START,
        SELECT,
        INCREASE,
        DECREASE
    };
public:
    TitleScene(SceneManager& sceneManager);
    ‾TitleScene();
    void Start() override;
    void Update() override;
    void Draw() const override;
    void End() override;
    bool IsSceneEnd() const override;
    virtual std::string Next() const override;
    void EndScene() override;
private:
    void IncreaseLevel();
    void DecreaseLevel();
    //キーがおされるまで待機
    void WaitToPressKey();
    //ステージ選択
    void SelectStage();
    //次のステージへスクロール
    void ScrollNextStage();
    //前のステージへスクロール
    void ScrollPrevStage();

private:
    State state_ = START;
    int levelNum_ = 1;
    int levelNameY_ = 500;
    bool isFadingEnd_ = false;
    bool isSceneEnd_ = false;
    SceneManager& sceneManager_;
};
#endif//!TITLE_SCENE_H_
