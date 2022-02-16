#pragma once
class Image
{
public:
	static int background;
	static int black;

	static int mapChip[24];
	static int player[8];
	static int thrownBox;
	static int boxItem;
	static int boxItemBlank;
	static int bubble;
	static int goal;
	static int cross;

	static int clearLogo;

	static int titleLogo;
	static int cover;
private:
	Image() = delete;
	‾Image() = delete;
public:
	static void Load();
	static void Delete();

};

