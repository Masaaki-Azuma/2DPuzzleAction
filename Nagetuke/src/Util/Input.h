#pragma once
class Input
{
private:
	Input() = delete;
	‾Input() = delete;

	static int prevInput;
	static int currentInput;

public:
	static void Init();
	static void Update();
	static bool GetButton(int buttonId);
	static bool GetButtonDown(int buttonId);
	static bool GetButtonUp(int buttonId);
};

