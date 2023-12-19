#include "framework.h"
#include "SceneManager.h"
#include "Scene.h"


void SceneManager::Init()
{

}

void SceneManager::Update(float deltaTime)
{
	if (_scene)
	{
		_scene->Update(deltaTime);
	}
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
	{
		_scene->Render(hdc);
	}
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
	{
		return;
	}

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::Engine3d:
		newScene = new olcEngine3D();
		break;
	
	}
	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}