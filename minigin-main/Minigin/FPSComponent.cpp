#include <stdexcept>
#include <SDL_ttf.h>
#include "FPSComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <format>

void bgn::FPSComponent::Update([[maybe_unused]] const float deltaTime)
{
	//calculate fps
	const float refreshTime = 0.5f; // how fast to refresh

	m_frameCounter++;
	m_timeCounter += deltaTime;

	if (m_timeCounter >= refreshTime)
	{
		//set text to fps
		SetText("FPS: " + std::format("{:.1f}", m_frameCounter / m_timeCounter));

		m_timeCounter -= refreshTime;
		m_frameCounter = 0;
	}

	TextComponent::Update(deltaTime);
}
