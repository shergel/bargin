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

#include "TextComponent.h"
#include "ImageComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = bgn::SceneManager::GetInstance().CreateScene("Demo");

#pragma region GameObject : Background
	auto go = std::make_shared<bgn::GameObject>();
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("background.tga");
	go->AddComponent(std::move(ic));
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Logo
	go = std::make_shared<bgn::GameObject>();
	ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("logo.tga");
	go->AddComponent(std::move(ic));
	go->SetPosition(216, 180);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Title
	go = std::make_shared<bgn::GameObject>();
	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_unique<bgn::TextComponent>("Programming 4 Assignment", font);
	go->AddComponent(std::move(tc));
	go->SetPosition(80, 20);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : FPS
	go = std::make_shared<bgn::GameObject>();
	auto fpsc = std::make_unique<bgn::FPSComponent>(font);
	go->AddComponent(std::move(fpsc));
	go->SetPosition(80, 400);
	scene.Add(go);
#pragma endregion
}

int main(int, char* []) {
	bgn::Bargin engine("../Data/");
	engine.Run(load);
	return 0;
}