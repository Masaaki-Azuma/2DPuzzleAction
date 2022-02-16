#include "AssetsManager/Font.h"
#include "DxLib.h"

int Font::fontHandle;

void Font::LoadFont(const char* fontName, int size)
{
    fontHandle = CreateFontToHandle(fontName, size, -1);
}

void Font::DeleteFont()
{
    DeleteFontToHandle(fontHandle);
}
