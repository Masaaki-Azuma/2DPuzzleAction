#pragma once

class MyMath
{
public:
	static const float PI;

private:
	MyMath() = delete;
	‾MyMath() = delete;

public:
	static bool RectRectIntersect(
		float aLeft, float aRight, float aTop, float aBottom,
		float bLeft, float bRight, float bTop, float bBottom);
};

