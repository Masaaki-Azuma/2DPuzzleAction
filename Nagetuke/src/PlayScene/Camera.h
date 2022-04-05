#pragma once
class Camera
{
private:
	static float x_;//左上x座標
	static float y_;//左上y座標
public:
	static float GetX() { return x_; }
	static float GetY() { return y_; }
	static void LookAt(float worldX, float worldY);
	static void DrawGraph(float worldX, float worldY, int handle, bool flip, float exRate = 1);
	static void DrawLineBox(float left, float top, float right, float bottom);
};

