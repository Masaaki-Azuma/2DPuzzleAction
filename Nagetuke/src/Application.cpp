#include "Application.h"

#include <DxLib.h>
#include "MyGame.h"
#include "Fps.h"
#include "Screen.h"

void Application::run()
{
	SetWindowText("ナゲツケ");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(Screen::Width, Screen::Height, 32);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	LPCSTR font_path = "Assets/Font/misaki_mincho.ttf";
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	SetDrawScreen(DX_SCREEN_BACK);	// DXライブラリ初期化処理

	MyGame game;
	Fps fps;

	game.Start();
	ScreenFlip();

	while (ProcessMessage() == 0) {
		fps.Update();//フレームレートの更新
		game.Update();//ゲーム本体の更新

		ClearDrawScreen();
		game.Draw();
		//fps.Draw();//フレームレートの描画
		ScreenFlip();
		fps.Wait();//60fps以上で動いていれば、60fpsになるよう待機
	}
	game.End();
	RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);
	DxLib_End();	// DXライブラリ終了処理
}
