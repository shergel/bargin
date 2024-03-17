#include "ImGuiCharts.h"
namespace bgn
{
	const RGBA ImGuiCharts::m_WHITE = { 255, 255, 255, 255 };
	const RGBA ImGuiCharts::m_ORANGE = { 255, 165, 0, 255 };
	const RGBA ImGuiCharts::m_TEAL = { 0, 128, 128, 255 };
	const RGBA ImGuiCharts::m_LIGHTBLUE = { 40,100, 255, 255 };
	void ImGuiCharts::Show()

	{
		ShowExercise1();
		ShowExercise2();
	}
	void ImGuiCharts::ShowExercise1()
	{
		if (ImGui::Begin("Exercise 1", nullptr))
		{
			// Widget : InputInt [-|+] # samples
			static int samples = 10;
			if (samples < 1) samples = 1; // clamp at [1,inf[
			ImGui::InputInt("# samples", &samples);

			// Widget : Button
			if (ImGui::Button("Trash the cache")) HandleButton1(samples);

			// Plot Integers
			if (m_showplots[0]) ImGui::Plot("Integers", m_plots[0]);
		}
		ImGui::End();
	}
	void ImGuiCharts::ShowExercise2()
	{
		if (ImGui::Begin("Exercise 2", nullptr))
		{
			// Widget : InputInt [-|+] # samples
			static int samples = 10;
			if (samples < 1) samples = 1; // clamp at [1,inf[
			ImGui::InputInt("# samples", &samples);

			// Widget : Button 1/2
			if (ImGui::Button("Trash the cache with GameObject3D")) HandleButton2(samples);
			// Plot GameObjects3D
			if (m_showplots[1]) ImGui::Plot("GameObjects3D", m_plots[1]);

			// Widget : Button 2/2
			if (ImGui::Button("Trash the cache with GameObject3DAlt")) HandleButton3(samples);
			// Plot GameObjects3DAlt
			if (m_showplots[2]) ImGui::Plot("GameObjects3DAlt", m_plots[2]);

			// Plot Combined - GameObjects3D & GameObjects3DAlt
			//if (m_showplots[1] && m_showplots[2]) {} ImGui::Plot("Combined Plot", m_plots[3]);
		}
		ImGui::End();
	}

	void ImGuiCharts::HandleButton1(const int samples)
	{
		//calculate and get averages
		std::vector<float> get = TrashTheCache::GetInstance().GetAveragesInts(samples);
		for (int i{}; i < m_amtData; ++i)
		{
			m_data[0][i] = get.at(i);
		}

		//update plot configs
		UpdatePlot(m_plots[0], m_data[0], m_ORANGE);

		//display
		m_showplots[0] = true;

	}
	void ImGuiCharts::HandleButton2(const int samples)
	{
		//calculate and get averages
		std::vector<float> get = TrashTheCache::GetInstance().GetAveragesGameObject3Ds(samples);
		for (int i{}; i < m_amtData; ++i)
		{
			m_data[1][i] = get.at(i);
		}

		UpdatePlot(m_plots[1], m_data[1], m_LIGHTBLUE);

		m_showplots[1] = true;
		if (m_showplots[2]) UpdateCombinedPlot();
	}
	void ImGuiCharts::HandleButton3(const int samples)
	{
		//calculate and get averages
		std::vector<float> get = TrashTheCache::GetInstance().GetAveragesGameObject3DAlts(samples);
		for (int i{}; i < m_amtData; ++i)
		{
			m_data[2][i] = get.at(i);
		}

		UpdatePlot(m_plots[2], m_data[2], m_TEAL);

		m_showplots[2] = true;
		if (m_showplots[1]) UpdateCombinedPlot();
	}

	void ImGuiCharts::UpdatePlot(ImGui::PlotConfig& conf, const float* ydata, RGBA rgba)
	{
		conf.values.ys = ydata;
		conf.values.count = m_amtData;
		conf.scale.min = -1;
		conf.scale.max = ydata[0];
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = m_plotSize;
		conf.line_thickness = 3.f;
		conf.values.color = IM_COL32(rgba.r, rgba.g, rgba.b, rgba.a);
	}
	void ImGuiCharts::UpdateCombinedPlot()
	{
		//todo : CALCULATE COMBINED PLOT.
		//Once finished, uncomment the last plot in ShowExercise2()
	}
}