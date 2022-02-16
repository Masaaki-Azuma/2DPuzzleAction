#pragma once
class Fade
{
public:
	enum State
	{
		WAIT,
		STOP,
		FADEIN,
		FADEOUT,
	};
private:
	int alpha_;
	State state_;
public:
	Fade();
	‾Fade() = default;
private:
	void FadeIn();
	void FadeOut();
public:
	void Update();
	void Draw();
	void Start(State state);
	bool IsWaiting();
	bool IsStoppping();
	bool IsRunning();
	void Reset();
};

