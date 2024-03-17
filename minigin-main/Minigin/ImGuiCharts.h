#pragma once
#include "Singleton.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../3rdParty/imgui-1.90.4/imgui.h"
#include "../3rdParty/imgui-1.90.4/imgui_plot.h"
#include <vector>
#include <numeric> 
#include <iostream>
#include <algorithm>
#include "TrashTheCache.h"

struct RGBA
{
	int r;
	int g;
	int b;
	int a;
};

namespace bgn
{
	class ImGuiCharts final : public Singleton<ImGuiCharts>
	{
	public:
		void Show();
	private:
		void ShowExercise1();
		void ShowExercise2();

		ImGui::PlotConfig m_plots[4]{};
		static const int m_amtData = 11;
		float m_data[3][m_amtData]{};
		bool m_showplots[3]{};

		static const RGBA m_WHITE;
		static const RGBA m_ORANGE;
		static const RGBA m_TEAL;
		static const RGBA m_LIGHTBLUE;
		const ImVec2 m_plotSize = ImVec2(200,100);

		void CalcPlot();
		void HandleButton1(const int samples);
		void HandleButton2(const int samples);
		void HandleButton3(const int samples);
		void UpdatePlot(ImGui::PlotConfig& conf, const float* ydata, RGBA rgba = m_WHITE);
		void UpdateCombinedPlot();
	};
}
