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
#include "PointsComponent.h"

#include "Observer.h"
#include "LifeObserver.h"
#include "PointsObserver.h"

#include "InputManager.h"
#include "Move2DCommand.h"
#include "AddSubtractHealthCommand.h"
#include "AddSubtractPointsCommand.h"
#include <memory>
#include <glm/vec2.hpp>

#include <steam_api.h>

std::shared_ptr<bgn::GameObject> LoadBackground();
std::shared_ptr<bgn::GameObject> LoadLogo();
std::shared_ptr<bgn::GameObject> LoadTitle(std::shared_ptr<bgn::Font> font);
std::shared_ptr<bgn::GameObject> LoadFPS(std::shared_ptr<bgn::Font> font);
std::shared_ptr<bgn::GameObject> LoadChar1();
std::shared_ptr<bgn::GameObject> LoadChar2();
std::shared_ptr<bgn::GameObject> LoadControls(std::shared_ptr<bgn::Font> font);
std::shared_ptr<bgn::GameObject> LoadDisplay(std::shared_ptr<bgn::Font> font);

bgn::LifeObserver g_lo1{}, g_lo2{}; //todo temporarily global, will fix in upcoming weeks! TODO
bgn::PointsObserver g_po1{}, g_po2{};



void load()
{
	auto font = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto font2 = bgn::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto& scene = bgn::SceneManager::GetInstance().CreateScene("Demo");

	scene.Add(LoadBackground());
	scene.Add(LoadLogo());
	scene.Add(LoadTitle(font));
	scene.Add(LoadFPS(font));
	scene.Add(LoadControls(font2));

	auto go = LoadChar1();
	go->AddObserver(&g_lo1);
	go->AddObserver(&g_po1);
	scene.Add(go);

	go = LoadChar2();
	go->AddObserver(&g_lo2);
	go->AddObserver(&g_po2);
	scene.Add(go);

	scene.Add(LoadDisplay(font2));
}


int main(int, char* []) {

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;

	bgn::Bargin engine("../Data/");
	engine.Run(load);

	
	SteamAPI_Shutdown();

	return 0;
}


std::shared_ptr<bgn::GameObject> LoadBackground()
{
	auto go = std::make_shared<bgn::GameObject>();
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("background.tga");
	go->AddComponent(std::move(ic));
	return go;
}


std::shared_ptr<bgn::GameObject> LoadLogo()
{
	auto go = std::make_shared<bgn::GameObject>();
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("logo.tga");
	go->AddComponent(std::move(ic));
	go->SetPivotPosition(216, 180);
	return go;
}


std::shared_ptr<bgn::GameObject> LoadTitle(std::shared_ptr<bgn::Font> font)
{
	auto go = std::make_shared<bgn::GameObject>();

	auto tc = std::make_unique<bgn::TextComponent>("Programming 4 Assignment", font);
	go->AddComponent(std::move(tc));
	go->SetPivotPosition(80, 20);
	return go;
}


std::shared_ptr<bgn::GameObject> LoadFPS(std::shared_ptr<bgn::Font> font)
{
	auto go = std::make_shared<bgn::GameObject>();
	auto fpsc = std::make_unique<bgn::FPSComponent>(font);
	go->AddComponent(std::move(fpsc));
	go->SetPivotPosition(80, 400);
	return go;
}


std::shared_ptr<bgn::GameObject> LoadChar1()
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
	/*points*/
	auto pc = std::make_unique<bgn::PointsComponent>();
	go->AddComponent(std::move(pc));
	/*position*/
	go->SetPivotPosition(346, 280);
	/*movement*/
	auto mc = std::make_unique<bgn::MovementComponent>();
	go->AddComponent(std::move(mc));

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
	std::unique_ptr<bgn::Command> addLife = std::make_unique<bgn::AddSubtractHealthCommand>(go, 1);
	bgn::InputManager::GetInstance().BindKey(SDLK_l, std::move(addLife));
	std::unique_ptr<bgn::Command> lowerLife = std::make_unique<bgn::AddSubtractHealthCommand>(go, -1);
	bgn::InputManager::GetInstance().BindKey(SDLK_k, std::move(lowerLife));

	/*points*/
	std::unique_ptr<bgn::Command> addPoints = std::make_unique<bgn::AddSubtractPointsCommand>(go, 20);
	bgn::InputManager::GetInstance().BindKey(SDLK_p, std::move(addPoints));

	return go;
}


std::shared_ptr<bgn::GameObject> LoadChar2()
{
	/*object*/
	auto go = std::make_shared<bgn::GameObject>();
	/*image*/
	auto ic = std::make_unique<bgn::ImageComponent>();
	ic->SetTexture("Child.tga");
	go->AddComponent(std::move(ic));
	/*health*/
	auto hc = std::make_unique<bgn::HealthComponent>(3, 1);
	go->AddComponent(std::move(hc));
	/*points*/
	auto pc = std::make_unique<bgn::PointsComponent>();
	go->AddComponent(std::move(pc));
	/*movement*/
	auto mc = std::make_unique<bgn::MovementComponent>();
	go->AddComponent(std::move(mc));
	/*position*/
	go->SetPivotPosition(446, 280);

	/*observer*/
	const float speed = 2.f;

	//commands
	std::unique_ptr<bgn::Command> moveLeft2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ -1,0 }, speed);
	std::unique_ptr<bgn::Command> moveRight2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 1,0 }, speed);
	std::unique_ptr<bgn::Command> moveUp2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,-1 }, speed);
	std::unique_ptr<bgn::Command> moveDown2 = std::make_unique<bgn::Move2DCommand>(go, glm::vec2{ 0,1 }, speed);

	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Left, std::move(moveLeft2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Right, std::move(moveRight2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Up, std::move(moveUp2));
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::DPad_Down, std::move(moveDown2));

	/*life*/
	std::unique_ptr<bgn::Command> addLife2 = std::make_unique<bgn::AddSubtractHealthCommand>(go, 1);
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::X, std::move(addLife2));
	std::unique_ptr<bgn::Command> lowerLife2 = std::make_unique<bgn::AddSubtractHealthCommand>(go, -1);
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::A, std::move(lowerLife2));

	/*points*/
	std::unique_ptr<bgn::Command> addPoints2 = std::make_unique<bgn::AddSubtractPointsCommand>(go, 20);
	bgn::InputManager::GetInstance().BindController(bgn::InputManager::ControllerKey::B, std::move(addPoints2));
	return go;
}

std::shared_ptr<bgn::GameObject> LoadControls(std::shared_ptr<bgn::Font> font)
{
	float xpos{ 20 }, ypos{ 100 };
	/*controls*/
	auto go = std::make_shared<bgn::GameObject>();

	auto tc = std::make_unique<bgn::TextComponent>("YELLOW :  D-PAD (move),  A (--life),  X (++life),  B (++points)", font);
	go->AddComponent(std::move(tc));

	tc = std::make_unique<bgn::TextComponent>("ORANGE :  WASD (move),  K (--life),  L (++life),  P (++points)", font);
	tc->SetLocalPosition(0, 20);
	go->AddComponent(std::move(tc));

	go->SetPivotPosition(xpos, ypos);

	return go;
}

std::shared_ptr<bgn::GameObject> LoadDisplay(std::shared_ptr<bgn::Font> font)
{
	float xpos{ 20 }, ypos{ 250 };
	float yoffset = 20;
	
	/*display*/

	auto go = std::make_shared<bgn::GameObject>();
	auto tc = std::make_unique<bgn::TextComponent>("# lives : 3", font);
	go->AddComponent(std::move(tc));

	tc = std::make_unique<bgn::TextComponent>("Score : 0", font);
	tc->SetLocalPosition(0, yoffset * 1);
	go->AddComponent(std::move(tc));

	tc = std::make_unique<bgn::TextComponent>("# lives : 3", font);
	tc->SetLocalPosition(0, yoffset * 2);
	go->AddComponent(std::move(tc));

	tc = std::make_unique<bgn::TextComponent>("Score : 0", font);
	tc->SetLocalPosition(0, yoffset * 3);
	go->AddComponent(std::move(tc));

	go->SetPivotPosition(xpos, ypos);

	return go;
}
