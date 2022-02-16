#include "Sound.h"
#include "DxLib.h"

int Sound::boxThrow;
int Sound::stickBlock;
int Sound::beep;
int Sound::clear;
int Sound::gather;
int Sound::getItem;
int Sound::jump;
int Sound::death;
int Sound::cursorMove;
int Sound::select;

void Sound::LoadSE()
{
	boxThrow = LoadSoundMem("Assets/SE/Motion-Swish03-1.mp3");
	stickBlock = LoadSoundMem("Assets/SE/Motion-Pop08-3.mp3");
	beep = LoadSoundMem("Assets/SE/クイズ不正解2.mp3");
	clear = LoadSoundMem("Assets/SE/Jingle#01.mp3");
	gather = LoadSoundMem("Assets/SE/パッ.mp3");
	getItem = LoadSoundMem("Assets/SE/パパッ.mp3");
	jump = LoadSoundMem("Assets/SE/SNES-Action01-01(Jump).mp3");
	death = LoadSoundMem("Assets/SE/Onmtp-Negative06-1.mp3");
	cursorMove = LoadSoundMem("Assets/SE/カーソル移動3.mp3");
	select = LoadSoundMem("Assets/SE/決定、ボタン押下34.mp3");
}

void Sound::PlayBGM(const char* fileName, int volume)
{
	//StopSoundFile();
	PlayMusic(fileName, DX_PLAYTYPE_LOOP);
	SetVolumeMusic(volume);
}

void Sound::StopBGM()
{
	StopMusic();
}

void Sound::ChangeVolume(int volume)
{
	SetVolumeMusic(volume);
}

void Sound::PlaySE(int soundHandle)
{
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

void Sound::Delete()
{
	InitSoundMem();
}
