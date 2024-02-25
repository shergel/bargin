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
#include "TextObject.h"
#include "Scene.h"

void load()
{
	auto& scene = bgn::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<bgn::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<bgn::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<bgn::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) {
	bgn::Bargin engine("../Data/");
	engine.Run(load);
    return 0;
}