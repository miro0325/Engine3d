#pragma once

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);

public:
	void ChangeScene(SceneType sceneType);

private:
	class Scene* _scene;
	SceneType _sceneType = SceneType::None;
};