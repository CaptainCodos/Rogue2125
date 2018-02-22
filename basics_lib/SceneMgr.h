#pragma once
#include "Scene.h"

class SceneMgr
{
public:
	static SceneMgr* GetInstance();

	void PushScene(std::shared_ptr<Scene> scene);

	std::vector<std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Scene> m_activeScene;
	
	// updates the currently active scene
	void UpdateActive(double dt);
	void DrawActive();
private:
	static SceneMgr* m_instance;
	SceneMgr(); // cannot be called outside class
	~SceneMgr() = default;
	SceneMgr(SceneMgr const&) {} // private copy constructor
	SceneMgr& operator=(SceneMgr const&) {} // private assignment
};

