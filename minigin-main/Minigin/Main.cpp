#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Bargin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "TextObject.h"

#include "ImageComponent.h"



void load()
{
	auto& scene = bgn::SceneManager::GetInstance().CreateScene("Demo");

#pragma region GameObject : Background
	auto go = std::make_shared<bgn::GameObject>();
	auto c = std::make_unique<bgn::ImageComponent>();
	c->SetTexture("background.tga");
	go->AddComponent(std::move(c));
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Logo
	go = std::make_shared<bgn::GameObject>();
	c = std::make_unique<bgn::ImageComponent>();
	c->SetTexture("logo.tga");
	go->AddComponent(std::move(c));
	go->SetPosition(216, 180);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Title
	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<bgn::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);
#pragma endregion
}

int main(int, char* []) {
	bgn::Bargin engine("../Data/");
	engine.Run(load);
	return 0;
}