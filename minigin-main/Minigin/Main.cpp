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

#include "InputManager.h"
#include "Move2DCommand.h"
#include "AdjustHealthCommand.h"
#include <memory>
#include <glm/vec2.hpp>

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
	go->SetPivotPosition(216, 180);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Title
	go = std::make_shared<bgn::GameObject>();
	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_unique<bgn::TextComponent>("Programming 4 Assignment", font);
	go->AddComponent(std::move(tc));
	go->SetPivotPosition(80, 20);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : FPS
	go = std::make_shared<bgn::GameObject>();
	auto fpsc = std::make_unique<bgn::FPSComponent>(font);
	go->AddComponent(std::move(fpsc));
	go->SetPivotPosition(80, 400);
	scene.Add(go);
#pragma endregion

#pragma region GameObject : Char1
	/*object*/
	go = std::make_shared<bgn::GameObject>();
	/*image*/
	ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("Parent.tga");
	go->AddComponent(std::move(ic));
	/*health*/
	//const int maxHealth = 5;
	auto hc = std::make_unique<bgn::HealthComponent>();
	go->AddComponent(std::move(hc));
	/*position*/
	go->SetPivotPosition(346, 280);
	/*movement*/
	auto mc = std::make_unique<bgn::MovementComponent>();
	go->AddComponent(std::move(mc));
	//auto rc = std::make_unique<bgn::RotationComponent>();
	//go->AddComponent(std::move(rc));
	scene.Add(go);

	float speed = 1.f; //the speed of go 2 will be double the speed of go 1

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
	std::unique_ptr<bgn::Command> decreaseHealth = std::make_unique<bgn::AdjustHealthCommand>(go, -1);
	bgn::InputManager::GetInstance().BindKey(SDLK_k, std::move(decreaseHealth));
	std::unique_ptr<bgn::Command> increaseHealth = std::make_unique<bgn::AdjustHealthCommand>(go, 1);
	bgn::InputManager::GetInstance().BindKey(SDLK_l, std::move(increaseHealth));
#pragma endregion

#pragma region GameObject : Char2
	/*object*/
	go = std::make_shared<bgn::GameObject>();
	/*image*/
	ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("Child.tga");
	go->AddComponent(std::move(ic));
	/*health*/
	hc = std::make_unique<bgn::HealthComponent>();
	go->AddComponent(std::move(hc));
	/*position*/
	go->SetPivotPosition(446, 280);
	/*add to scene*/
	scene.Add(go);
	
	//commands
	std::unique_ptr<bgn::Command> moveLeft2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ -1,0 }, speed * 2);
	std::unique_ptr<bgn::Command> moveRight2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 1,0 }, speed * 2);
	std::unique_ptr<bgn::Command> moveUp2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,-1 }, speed * 2);
	std::unique_ptr<bgn::Command> moveDown2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,1 }, speed * 2);

	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Left, std::move(moveLeft2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Right, std::move(moveRight2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Up, std::move(moveUp2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Down, std::move(moveDown2));
#pragma endregion

	//#pragma region GameObject : Child
	//	auto go2 = std::make_shared<bgn::GameObject>();
	//	ic = std::make_unique<bgn::ImageComponent>();
	//	ic->SetTexture("Child.tga");
	//	go2->AddComponent(std::move(ic));
	//	go2->SetParent(go.get(), false);
	//	go2->SetLocalPosition(40,40);
	//
	//	auto rc2 = std::make_unique<bgn::RotationComponent>(2.f,10.f);
	//	//go2->AddComponent(std::move(rc2));
	//	scene.Add(go2);
	//#pragma endregion
}

int main(int, char* []) {
	bgn::Bargin engine("../Data/");
	engine.Run(load);
	return 0;
}