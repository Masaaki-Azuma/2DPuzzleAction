#include "ClearScene/ClearScene.h"
#include "DxLib.h"
#include "AssetsManager/Image.h"
#include "Util/Input.h"
#include "AssetsManager/Sound.h"
#include "AssetsManager/Font.h"
#include "SceneManager.h"

ClearScene::ClearScene(SceneManager* sceneManager)
{
	sceneManager_ = sceneManager;
}

ClearScene::‾ClearScene()
{
}

void ClearScene::Start()
{
	isFadingEnd_ = false;
	isSceneEnd_ = false;
	Sound::StopBGM();
	Sound::PlaySE(Sound::clear);
}

void ClearScene::Update()
{
	if (isFadingEnd_) {
		sceneManager_->LoadMapNextLevel();
		sceneManager_->EndOverlap();
		sceneManager_->StartFade(Fade::FADEIN);
		return;
	}

	if (Input::GetButtonDown(PAD_INPUT_A)) {
		sceneManager_->StartFade(Fade::FADEOUT);
		isFadingEnd_ = true;
	}
}

void ClearScene::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, Image::black, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(340, 200, Image::clearLogo, TRUE);
	DrawStringToHandle(360, 500, "Press A To Next Stage", GetColor(255, 255, 255), Font::fontHandle);  //TODO:フォントへのアクセスの解決
}

bool ClearScene::IsSceneEnd() const
{
	return isSceneEnd_;
}

std::string ClearScene::Next() const
{
	return "NullScene";
}
