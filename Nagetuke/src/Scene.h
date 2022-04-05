#ifndef SCENE_H_
#define SCENE_H_

#include <string>

class SceneManager;

class Scene
{
public:
	Scene(SceneManager& sceneManager):
		sceneManager_{sceneManager}
	{}
	virtual ‾Scene() = default;
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual void End() = 0;
	virtual bool IsSceneEnd() const = 0;
	virtual std::string Next() const = 0;
	virtual void EndScene() = 0;
protected:
	bool isFadingEnd_ = false;
	bool isSceneEnd_ = false;
	SceneManager& sceneManager_;
};
#endif//!SCENE_H_
