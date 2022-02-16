#include "TitleScene/TitleScene.h"
#include "DxLib.h"
#include "Util/Input.h"
#include "AssetsManager/Image.h"
#include "AssetsManager/Sound.h"
#include "AssetsManager/Font.h"
#include "PlayScene/Map.h"
#include "SceneManager.h"

TitleScene::TitleScene(SceneManager& sceneManager):
	sceneManager_{sceneManager}
{

}

TitleScene::‾TitleScene()
{
}

void TitleScene::Start()
{
	//フラグを初期化
	isFadingEnd_ = false;
	isSceneEnd_ = false;
	Sound::PlayBGM("Assets/BGM/コイントス.mp3", 150);
	sceneManager_.StartFade(Fade::FADEIN);
}

void TitleScene::Update()
{
	//画面状態によって遷移
	switch (state_) {
	case START:    WaitToPressKey();  break;
	case SELECT:   SelectStage();     break;
	case INCREASE: ScrollNextStage(); break;
	case DECREASE: ScrollPrevStage(); break;
	}
}

void TitleScene::Draw() const
{
	const int fontHandle = Font::fontHandle;

	DrawGraph(0, 0, Image::background, false);
	DrawGraph(340, 150, Image::titleLogo, true);
	if(state_ == START) {
		DrawStringToHandle(390, 550, "Press A Key To Start", GetColor(0, 0, 0), fontHandle);
	}
	else {
		bool canDecrease = levelNum_ > 1;
		bool canIncrease = levelNum_ < Map::MaxLevel_;
		if(canDecrease) DrawFormatStringToHandle(530, levelNameY_ - 50, GetColor(0, 0, 0), fontHandle, "Stage %d", levelNum_ - 1);

		DrawFormatStringToHandle(530, levelNameY_, GetColor(0, 0, 0), fontHandle, "Stage %d", levelNum_);
		if (levelNameY_ == 500) DrawStringToHandle(425, 500, ">>>          <<<", GetColor(0, 0, 0), fontHandle);
		DrawGraph(510, 370, Image::cover, false);

		if (canIncrease) DrawFormatStringToHandle(530, levelNameY_ + 50, GetColor(0, 0, 0), fontHandle, "Stage %d", levelNum_ + 1);
		DrawGraph(510, 570, Image::cover, false);

		if (canDecrease) DrawStringToHandle(600, 400, "▲", GetColor(0, 0, 0), fontHandle); 
		if (canIncrease) DrawStringToHandle(600, 600, "▼", GetColor(0, 0, 0), fontHandle);
			
	}
}

void TitleScene::End()
{
}

bool TitleScene::IsSceneEnd() const
{
	return isSceneEnd_;
}

std::string TitleScene::Next() const
{
	return "PlayScene";
}

void TitleScene::EndScene()
{
	isSceneEnd_ = true;
}

void TitleScene::IncreaseLevel()
{
	state_ = INCREASE;
}

void TitleScene::DecreaseLevel()
{
	state_ = DECREASE;
}

void TitleScene::WaitToPressKey()
{
	if (Input::GetButtonDown(PAD_INPUT_A)) {
		state_ = SELECT;
		Sound::PlaySE(Sound::select);
		return;
	}
}

void TitleScene::SelectStage()
{
	//終了した次のフレームで変わる
	if (isFadingEnd_) {
		sceneManager_.SetMapLevel(levelNum_);
		isSceneEnd_ = true;
		return;
	}

	if (Input::GetButtonDown(PAD_INPUT_A)) 		{
		Sound::PlaySE(Sound::select);
		sceneManager_.StartFade(Fade::FADEOUT);
		isFadingEnd_ = true;
	}

	if (Input::GetButton(PAD_INPUT_DOWN) && levelNum_ < Map::MaxLevel_) {
		//次ステージへスクロール状態に遷移
		IncreaseLevel();
		Sound::PlaySE(Sound::cursorMove);
	}
	else if (Input::GetButton(PAD_INPUT_UP) && levelNum_ > 1) {
		//前ステージへスクロール状態に遷移
		DecreaseLevel();
		Sound::PlaySE(Sound::cursorMove);
	}
}

void TitleScene::ScrollNextStage()
{
	levelNameY_ -= 5;
	if (levelNameY_ <= 450) {
		levelNameY_ = 500;
		levelNum_++;
		state_ = SELECT;
	}
}

void TitleScene::ScrollPrevStage()
{
	levelNameY_ += 5;
	if (levelNameY_ >= 550) {
		levelNameY_ = 500;
		levelNum_--;
		state_ = SELECT;
	}
}

