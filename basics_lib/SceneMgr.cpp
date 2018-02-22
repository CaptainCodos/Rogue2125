#include "SceneMgr.h"
#include "RenderSystem.h"

using namespace std;
using namespace sf;

SceneMgr* SceneMgr::m_instance = NULL;

SceneMgr::SceneMgr()
{
	m_scenes = std::vector<std::shared_ptr<Scene>>();
}

void SceneMgr::PushScene(std::shared_ptr<Scene> scene)
{
	if (m_scenes.size() <= 0)
	{
		m_scenes.push_back(scene);
		m_activeScene = scene;
	}
	else
	{
		m_scenes.push_back(scene);
	}
}

SceneMgr* SceneMgr::GetInstance()
{
	if (!m_instance)
		m_instance = new SceneMgr();

	return m_instance;
}

void SceneMgr::UpdateActive(double dt)
{
	m_activeScene->UpdateScene(dt);
}

void SceneMgr::DrawActive()
{
	m_activeScene->DrawScene();
}
