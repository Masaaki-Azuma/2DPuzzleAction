#pragma once
class Effect
{
protected:
	float x_;
	float y_;
	int timer_;
public:
	bool isDead_;
protected:
	Effect() = default;
protected:
	void Die() { isDead_ = true; }
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

