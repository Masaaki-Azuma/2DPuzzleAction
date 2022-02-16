#pragma once

class Font
{
public:
	static int fontHandle;
public:
	static void LoadFont(const char* fontName, int size);
	static void DeleteFont();
};

