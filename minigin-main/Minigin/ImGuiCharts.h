#pragma once
#include "Singleton.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../3rdParty/imgui-1.90.4/imgui.h"
#include <vector>
#include <numeric> 
#include <iostream>
#include <algorithm>

namespace bgn
{
	class ImGuiCharts final : public Singleton<ImGuiCharts>
	{
	public:
		void Show();
	private:
		void ShowExercise1();
		void ShowExercise2();

		void Temp_PrintNumber(int inp);
		void Temp_PrintNumber1(int inp);
		void Temp_PrintNumber2(int inp);
	};
}

namespace bgn
{
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
			static int samples = 100;
			ImGui::InputInt("# samples", &samples);

			// Widget : Button
			if (ImGui::Button("Trash the cache"))
			{
				Temp_PrintNumber(samples);
			}
		}
		ImGui::End();
	}

	void ImGuiCharts::ShowExercise2()
	{
		if (ImGui::Begin("Exercise 2", nullptr))
		{
			// Widget : InputInt [-|+] # samples
			static int samples = 100;
			ImGui::InputInt("# samples", &samples);

			// Widget : Button 1/2
			if (ImGui::Button("Trash the cache with GameObject3D"))
			{
				Temp_PrintNumber1(samples);
			}

			// Widget : Button 2/2
			if (ImGui::Button("Trash the cache with GameObject3DAlt"))
			{
				Temp_PrintNumber2(samples);
			}
		}
		ImGui::End();
	}

	void ImGuiCharts::Temp_PrintNumber(int inp)
	{
		std::vector<int> vec = { 1, 4, 5, 63, 4, 2, -2, 4 };

		// Calculate the sum of non-negative elements in the vector
		int sum = std::accumulate(vec.begin(), vec.end(), 0, [](int acc, int x) {
			return x >= 0 ? acc + x : acc;
			});

		// Calculate the count of non-negative elements
		int count = int(std::count_if(vec.begin(), vec.end(), [](int x) {
			return x >= 0;
			}));

		// Calculate the average
		double average = static_cast<double>(sum) / count;

		// Print the average
		std::cout << "\nAverage of non-negative numbers: " << average << "   " + std::to_string(inp) << std::endl;
	}

	void ImGuiCharts::Temp_PrintNumber1(int inp)
	{
		std::cout << "\nButton 1 was called " << inp << std::endl;
	}

	void ImGuiCharts::Temp_PrintNumber2(int inp)
	{
		// Print the average
		std::cout << "\nButton 2 was called " << inp << std::endl;
	}
}