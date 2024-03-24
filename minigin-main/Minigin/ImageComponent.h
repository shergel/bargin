#pragma once
#include <memory>
#include "Component.h"
#include "Texture2D.h"
#include <iostream>

namespace bgn
{
	class ImageComponent : public Component
	{
	public:
		ImageComponent() = default;
		~ImageComponent() = default;

		virtual void Render() const;
		void SetTexture(const std::string& filename);
		void SetVisible(bool visible = true) { m_visible = visible; }
	private:
		std::shared_ptr<Texture2D> m_texture{};
		bool m_visible{ true };
	};
}