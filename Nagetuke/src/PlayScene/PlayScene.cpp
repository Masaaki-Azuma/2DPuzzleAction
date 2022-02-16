#include "PlayScene.h"

#include <algorithm>//for_each
#include <DxLib.h>

#include "Util/Input.h"
#include "Util/MyMath.h"
#include "AssetsManager/Sound.h"
#include "Game.h"
#include "Map.h"
#include "PlayScene/Camera.h"
#include "TitleScene/TitleScene.h"
#include "GameObject/Player.h"
#include "Effect/Effect.h"
#include "SceneManager.h"

/*TODO:
ヘッダファイルの掃除
MapからFadeを分離
*/
//TODO:
//不要なコンストラクタの削除
//カメラを分離

PlayScene::PlayScene(SceneManager& sceneManager):
	Scene{sceneManager}
{
}

PlayScene::‾PlayScene()
{
}

void PlayScene::Start()
{
	//フラグを初期化
	isFadingEnd_ = false;
	isSceneEnd_ = false;
	if (!map_) {
		map_ = sceneManager_.GetMapPtr();
	}
	if (!map_->playScene_) {
		map_->playScene_ = this;
	}
	sceneManager_.StartFade(Fade::FADEIN);
	map_->LoadLevel();
	Camera::LookAt(player_->GetX(), player_->GetY());
}

void PlayScene::Update()
{
	//暗転中に現レベルをロードし、フェードインする
	if (isLevelEnd_) {
		sceneManager_.StartFade(Fade::FADEIN);
		map_->LoadLevel();
		Camera::LookAt(player_->GetX(), player_->GetY());
		isLevelEnd_ = false;
		return;
	}

	//ポース画面を開く
	if (Input::GetButtonDown(PAD_INPUT_R)) {//START
		sceneManager_.SetOverlappingScene("PauseScene");
		return;
	}

	int gameObjects_Size = gameObjects_.size();
	for (int i = 0; i < gameObjects_Size; i++) {//範囲ベースfor文内で、要素数をを変えてはいけない
		gameObjects_.at(i)->Update();
	}

	if(map_->GetCurrentLevel() != 0) Camera::LookAt(player_->GetX(), player_->GetY());

	for (auto& e : effects_) {
		e->Update();
	}

	//衝突判定
	for (int i = 0; i < gameObjects_Size; i++) {
		auto& a = gameObjects_.at(i);
		if (a->isDead_) continue;
		for (int j = i + 1; j < gameObjects_Size; j++) {
			auto& b = gameObjects_.at(j);
			if (b->isDead_) continue;

			bool isCollided = MyMath::RectRectIntersect(a->GetLeft(), a->GetRight(), a->GetTop(), a->GetBottom(),
				                                        b->GetLeft(), b->GetRight(), b->GetTop(), b->GetBottom());
			if (isCollided) {
				a->OnCollision(*b);
				b->OnCollision(*a);
			}
		}
	}

	//死んだオブジェクトを削除
	auto resultOb = std::remove_if(gameObjects_.begin(), gameObjects_.end(), [](auto& go) {return go->isDead_; });
	gameObjects_.erase(resultOb, gameObjects_.end());
	player_->ArrangeBoxes();

	//死んだエフェクトを削除
	auto resultEf = std::remove_if(effects_.begin(), effects_.end(), [](auto& e) {return e->isDead_; });
	effects_.erase(resultEf, effects_.end());

	//なぜかdelete後もUpdateを最後まで実行してくれる
	//ChangeSceneは実質自殺なので、切り替えの遅延が必要
	//Updateの最後に切り替えるのが良い（Draw後に切り替えると前シーンを見ながら後シーンの操作をすることになる）
}

void PlayScene::Draw() const
{
	map_->Draw();
	for(const auto& go : gameObjects_)
	{
		go->Draw();
	}

	for (const auto& e : effects_) {
		e->Draw();
	}
}

void PlayScene::End()
{
	effects_.clear();
	gameObjects_.clear();
	player_.reset();
}

bool PlayScene::IsSceneEnd() const
{
	return isSceneEnd_;
}

std::string PlayScene::Next() const
{
	return "TitleScene";
}

void PlayScene::RestartLevel()
{
	sceneManager_.StartFade(Fade::FADEOUT);
	isLevelEnd_ = true;
}

bool PlayScene::IsBlock(float x, float y)
{
	return map_->IsBlock(x, y);
}

bool PlayScene::IsNeedle(float x, float y)
{
	return map_->IsNeedle(x, y);
}

void PlayScene::GameClear()
{
	sceneManager_.SetOverlappingScene("ClearScene");
}
