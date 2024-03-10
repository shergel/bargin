#pragma once
#include "Singleton.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../3rdParty/imgui-1.90.4/imgui.h"

namespace bgn
{
	class ImGuiCharts final : public Singleton<ImGuiCharts>
	{
	public:
		void Show();
	private:
	};
}

namespace bgn
{
	void ImGuiCharts::Show()
	{
		if (ImGui::Begin("My Window", nullptr))
		{

		}ImGui::End();
	}
}