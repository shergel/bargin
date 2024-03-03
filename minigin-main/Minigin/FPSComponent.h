#pragma once
#include "TextComponent.h"

namespace bgn
{
	class Font;
	class Texture2D;
	class FPSComponent final : public TextComponent
	{
	public:
		void Update(float deltaTime) override;
		FPSComponent(std::shared_ptr<Font> font) : TextComponent("FPS: ...LOADING", font) {}
		~FPSComponent() = default;
	private:
		float m_timeCounter{};
		int m_frameCounter{};
	};
}
