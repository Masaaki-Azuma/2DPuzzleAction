#pragma once

class PlayScene;

class GameObject
{
protected:
	float x_;
	float y_;
	float prevX_;
	float prevY_;
	PlayScene* playScene_;
	int imageWidth_;
	int imageHeight_;
	int hitboxOffsetLeft_;
	int hitboxOffsetRight_;
	int hitboxOffsetTop_;
	int hitboxOffsetBottom_;
public:
	bool isDead_;
protected:
	GameObject(float x, float y, PlayScene* playScene, int width, int height);
public:
	virtual ‾GameObject() = default;
protected:
	//判定方向を引数にすることも考えたが、右・左、上・下で処理が若干異なるので個別に用意
	bool MoveCloseToRightBlock();
	bool MoveCloseToLeftBlock();
	bool MoveCloseToAboveBlock();
	bool MoveCloseToBottomBlock();
	bool IsBlock(float worldX, float worldY);
	bool IsNeedle(float worldX, float worldY);
public:
	float GetX() const { return x_; }
	float GetY() const { return y_; }
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;
	float GetPrevLeft() const;
	float GetPrevRight() const;
	float GetPrevTop() const;
	float GetPrevBottom() const;
	bool isDead() const { return isDead_; }
	void StorePrevState();
	void SetLeft(float left);
	void SetRight(float right);
	void SetTop(float top);
	void SetBottom(float bottom);
	virtual void OnCollision(GameObject& other) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawGUI() {}
	void DrawHitBox();
};

