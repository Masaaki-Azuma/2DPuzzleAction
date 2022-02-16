#include "Input.h"
#include "DxLib.h"

//staticメンバを実体化
int Input::prevInput;
int Input::currentInput;

void Input::Init()
{
	prevInput = 0;
	currentInput = 0;
}

void Input::Update()
{
	prevInput = currentInput;
	currentInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

bool Input::GetButton(int buttonId)
{
	return (currentInput & buttonId) != 0;
}

bool Input::GetButtonDown(int buttonId)
{
	return ((currentInput & buttonId) & ‾(prevInput & buttonId)) != 0;
}

bool Input::GetButtonUp(int buttonId)
{
	return ((prevInput & buttonId) & ‾(currentInput & buttonId)) != 0;
}

