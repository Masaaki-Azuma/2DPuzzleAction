#pragma once
#include "Game.h"
#include "DxLib.h"
#include "Input.h"
#include "Image.h"
#include "Sound.h"
#include "Font.h"

#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "PauseScene.h"
#include "ClearScene.h"

//ゲーム固有の処理を担当する派生クラス
//事実上のメイン関数
class MyGame :
    public Game
{
    SceneManager sceneManager_;
public:
    void Start() override
    {
        Font::LoadFont("美咲明朝", 45);
        Input::Init();
        Image::Load();
        Sound::LoadSE();

        sceneManager_.Add("TitleScene", new TitleScene(&sceneManager_));
        sceneManager_.Add("PlayScene", new PlayScene(&sceneManager_));
        sceneManager_.Add("PauseScene", new PauseScene(&sceneManager_));
        sceneManager_.Add("ClearScene", new ClearScene(&sceneManager_));

        sceneManager_.Change("TitleScene");
    }
    void Update() override
    {
        Input::Update();
        sceneManager_.Update();
    }
    void Draw()
    {
        sceneManager_.Draw();
    }
    void End()
    {
        sceneManager_.End();
        Sound::Delete();
        Image::Delete();
        Font::DeleteFont();
    }
};
