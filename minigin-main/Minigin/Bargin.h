#pragma once
#include <string>
#include <functional>

namespace bgn
{
	class Bargin
	{
	public:
		explicit Bargin(const std::string& dataPath);
		~Bargin();
		void Run(const std::function<void()>& load);

		Bargin(const Bargin& other) = delete;
		Bargin(Bargin&& other) = delete;
		Bargin& operator=(const Bargin& other) = delete;
		Bargin& operator=(Bargin&& other) = delete;
	};
}