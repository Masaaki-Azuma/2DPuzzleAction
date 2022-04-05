#pragma once

class Sound
{
public:
	static int boxThrow;
	static int stickBlock;
	static int beep;
	static int clear;
	static int gather;
	static int getItem;
	static int jump;
	static int death;
	static int cursorMove;
	static int select;
public:
	static void LoadSE();
	static void PlayBGM(const char* fileName, int volume = 255);
	static void StopBGM();
	static void ChangeVolume(int volume);
	static void PlaySE(int soundHandle);
	static void Delete();
};

