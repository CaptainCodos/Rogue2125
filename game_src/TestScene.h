#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene() = default;

	void UpdateScene(double dt) override;
	void DrawScene() override;
	void LoadScene() override;
};