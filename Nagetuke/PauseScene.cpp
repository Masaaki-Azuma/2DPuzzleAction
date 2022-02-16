#include "PauseScene.h"
#include "DxLib.h"
#include "Image.h"
#include "Sound.h"
#include "Input.h"
#include "Font.h"
#include "Game.h"
#include "TitleScene.h"
#include <string>
#include "SceneManager.h"

const int MaxOption = 2;

PauseScene::PauseScene(SceneManager* sceneManager)
{
	sceneManager_ = sceneManager;
}

PauseScene::‾PauseScene()
{
}

void PauseScene::Start()
{
	isFadingEnd_ = false;
	isSceneEnd_ = false;
	Sound::ChangeVolume(150);
}

void PauseScene::Update()
{
	if (isFadingEnd_) {
		sceneManager_->EndCurrentScene();
		isSceneEnd_ = true;
		return;
	}

	if (Input::GetButtonDown(PAD_INPUT_UP)) {
		selectedOption_ = (selectedOption_ + MaxOption - 1) % MaxOption;
	}
	else if (Input::GetButtonDown(PAD_INPUT_DOWN)) {
		selectedOption_ = (selectedOption_ + 1) % MaxOption;
	}

	if (Input::GetButtonDown(PAD_INPUT_A))
	{
		Option option = (Option)selectedOption_;
		if (option == RETURN) {
			Sound::ChangeVolume(220);
			sceneManager_->EndOverlap();
		}
		else if (option == TITLE) {
			sceneManager_->StartFade(Fade::FADEOUT);
			isFadingEnd_ = true;
		}
	}

	if (Input::GetButtonDown(PAD_INPUT_R)) {//START
		Sound::ChangeVolume(220);
		sceneManager_->EndOverlap();
	}
}

bool PauseScene::IsSceneEnd() const
{
	return isSceneEnd_;
}

std::string PauseScene::Next() const
{
	return "NullScene";
}

void PauseScene::Draw() const
{
	const int fontHandle = Font::fontHandle;
	static const unsigned int color = GetColor(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, Image::black, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	static const int baseX = 580;
	static const int baseY = 400;
	static const int space = 60;

	static const char* optionNames[MaxOption] = {"Return", "Title"};
	DrawStringToHandle(580, 250, "PAUSE", color, fontHandle);
	for (int i = 0; i < MaxOption; i++) {
		DrawStringToHandle(baseX, baseY + space * i, optionNames[i], color, fontHandle);
	}
	DrawStringToHandle(baseX - 120, baseY + space * selectedOption_, ">>>          <<<", color, fontHandle);
}
