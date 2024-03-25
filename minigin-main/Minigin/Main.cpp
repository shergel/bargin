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
#include "RotationComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"

#include "Observer.h"
#include "LifeObserver.h"

#include "InputManager.h"
#include "Move2DCommand.h"
#include "AddSubtractHealthCommand.h"
#include <memory>
#include <glm/vec2.hpp>

std::shared_ptr <bgn::GameObject> LoadBackground();
std::shared_ptr <bgn::GameObject> LoadLogo();
std::shared_ptr <bgn::GameObject> LoadTitle(std::shared_ptr < bgn::Font> font);
std::shared_ptr <bgn::GameObject> LoadFPS(std::shared_ptr < bgn::Font> font);
std::shared_ptr <bgn::GameObject> LoadChar1();
std::shared_ptr <bgn::GameObject> LoadChar2();

bgn::LifeObserver g_lo{}; //todo temporarily global, will fix in upcoming weeks! TODO

void load()
{
	auto& scene = bgn::SceneManager::GetInstance().CreateScene("Demo");
	scene.Add(LoadBackground());
	scene.Add(LoadLogo());

	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	scene.Add(LoadTitle(font));
	scene.Add(LoadFPS(font));
	scene.Add(LoadChar1());
	scene.Add(LoadChar2());
}

int main(int, char* []) {
	bgn::Bargin engine("../Data/");
	engine.Run(load);
	return 0;
}

#pragma region loads
std::shared_ptr <bgn::GameObject> LoadBackground()
{
	auto go = std::make_shared<bgn::GameObject>();
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("background.tga");
	go->AddComponent(std::move(ic));
	return go;
}

std::shared_ptr <bgn::GameObject>  LoadLogo()
{
	auto go = std::make_shared<bgn::GameObject>();
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("logo.tga");
	go->AddComponent(std::move(ic));
	go->SetPivotPosition(216, 180);
	return go;
}

std::shared_ptr <bgn::GameObject>  LoadTitle(std::shared_ptr < bgn::Font> font)
{
	auto go = std::make_shared<bgn::GameObject>();
	auto tc = std::make_unique<bgn::TextComponent>("Programming 4 Assignment", font);
	go->AddComponent(std::move(tc));
	go->SetPivotPosition(80, 20);
	return go;
}

std::shared_ptr <bgn::GameObject>  LoadFPS(std::shared_ptr < bgn::Font> font)
{
	auto go = std::make_shared<bgn::GameObject>();
	auto fpsc = std::make_unique<bgn::FPSComponent>(font);
	go->AddComponent(std::move(fpsc));
	go->SetPivotPosition(80, 400);
	return go;
}

std::shared_ptr <bgn::GameObject>  LoadChar1()
{
	/*object*/
	auto go = std::make_shared<bgn::GameObject>();
	/*image*/
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("Parent.tga");
	go->AddComponent(std::move(ic));
	/*health*/
	//const int maxHealth = 5;
	auto hc = std::make_unique<bgn::HealthComponent>(3, 1);
	go->AddComponent(std::move(hc));
	/*position*/
	go->SetPivotPosition(346, 280);
	/*movement*/
	auto mc = std::make_unique<bgn::MovementComponent>();
	go->AddComponent(std::move(mc));

	float speed = 1.f; //the speed of go 2 will be double the speed of go 1

	/*observer*/
	go->AddObserver(&g_lo); //temporarily global, will fix in upcoming weeks! TODO

	//Commands
	/*movement*/
	std::unique_ptr<bgn::Command> moveLeft = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ -1,0 }, speed);
	std::unique_ptr<bgn::Command> moveRight = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 1,0 }, speed);
	std::unique_ptr<bgn::Command> moveUp = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,-1 }, speed);
	std::unique_ptr<bgn::Command> moveDown = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,1 }, speed);

	bgn::InputManager::GetInstance().BindKey(SDLK_a, std::move(moveLeft));
	bgn::InputManager::GetInstance().BindKey(SDLK_d, std::move(moveRight));
	bgn::InputManager::GetInstance().BindKey(SDLK_w, std::move(moveUp));
	bgn::InputManager::GetInstance().BindKey(SDLK_s, std::move(moveDown));

	/*life*/
	std::unique_ptr<bgn::Command> addLife = std::make_unique<bgn::AddSubtractHealthCommand>(go, 1);
	bgn::InputManager::GetInstance().BindKey(SDLK_l, std::move(addLife));
	std::unique_ptr<bgn::Command> lowerLife = std::make_unique<bgn::AddSubtractHealthCommand>(go, -1);
	bgn::InputManager::GetInstance().BindKey(SDLK_k, std::move(lowerLife));

	return go;
}

std::shared_ptr <bgn::GameObject>  LoadChar2()
{
	/*object*/
	auto go = std::make_shared<bgn::GameObject>();
	/*image*/
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("Child.tga");
	go->AddComponent(std::move(ic));
	/*health*/
	auto hc = std::make_unique<bgn::HealthComponent>();
	go->AddComponent(std::move(hc));
	/*position*/
	go->SetPivotPosition(446, 280);
	const float speed = 1.f;
	/*observer*/

	//commands
	std::unique_ptr<bgn::Command> moveLeft2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ -1,0 }, speed * 2);
	std::unique_ptr<bgn::Command> moveRight2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 1,0 }, speed * 2);
	std::unique_ptr<bgn::Command> moveUp2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,-1 }, speed * 2);
	std::unique_ptr<bgn::Command> moveDown2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,1 }, speed * 2);

	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Left, std::move(moveLeft2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Right, std::move(moveRight2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Up, std::move(moveUp2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Down, std::move(moveDown2));

	return go;
}
#pragma endregion