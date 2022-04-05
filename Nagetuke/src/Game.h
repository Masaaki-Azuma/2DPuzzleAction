#ifndef GAME_H_
#define GAME_H_

//ゲーム抽象インターフェース
class Game
{
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;
};

#endif//!GAME_H_
