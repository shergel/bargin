#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"

namespace bgn
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		virtual void Update(float deltaTime) override;
		void Render() const;

		void SetText(const std::string& text);
		void SetLocalPosition(float x, float y);

		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
