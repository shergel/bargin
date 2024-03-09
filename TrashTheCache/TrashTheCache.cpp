using namespace std;

#pragma region head
#include "TrashTheCache.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

#define CLEARLASTLINE	"\033[1A\033[K"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define WHITE   "\033[37m"
#define YELLOW  "\033[33m"

int main()
{
	Message message{};

	Init();
	Iterate();
	if (g_debug || g_timer)  message = AnnounceEnd(); 

	Deinit();
	std::cin.get();
}

void Init()
{
	Message message{};
	if (g_timer || g_debug) message = InitStart();

	for (int i{}; i < g_amtElements; ++i)
	{
		int* element = new int{};
		g_ints.push_back(element);
	}

	if (g_timer || g_debug) message = InitEnd();
}

void Iterate()
{
	/*debug*/
	Message message{};
	cout << setprecision(2) << fixed;
	if (g_timer || g_debug) message = AnnounceIterationStart();
	float percentage{};
	float percentage_prev = percentage;

	/*times*/
	chrono::steady_clock::time_point start{};
	chrono::steady_clock::time_point end{};
	long long time_delta{};

	/*calc*/
	const int maxPower = 10;
	int step{};

	for (int i{}; i <= maxPower; ++i)
	{
		int step = int(pow(2, i));

		if (g_timer) start = chrono::high_resolution_clock::now();
		for (int j{}; j < g_amtElements; j += step)
		{
			/* calc */
			percentage = float(j) / g_amtElements * 100;

			if (g_debug)
			{
				message = Loading(step, percentage);
				percentage_prev = percentage;
			}
		}
		if (g_debug) message = Done(step);

		if (g_timer)
		{
			end = chrono::high_resolution_clock::now();
			time_delta = chrono::duration_cast<chrono::microseconds>(end - start).count();
			message = PrintTime(step, time_delta);
		}
	}

}

void Deinit()
{
	for (int* element : g_ints)
	{
		delete element;
		element = nullptr;
	}
}

Message InitStart()
{
	Message output{};

	string message = " .:*-----[     INITIALIZING...     ]-----*:. ";
	cout << RED << "\n" << message << RESET;

	output.success = true;
	return output;
}

Message InitEnd()
{
	Message output{};

	string message = " .:*-----[     INITIALIZING : DONE    ]-----*:. ";
	cout << CLEARLASTLINE << WHITE << "\n" << message << "\n";

	output.success = true;
	return output;
}

Message AnnounceIterationStart()
{
	Message output{};

	string message = " .:*-----[     ITERATING OVER VECTOR IN INTERVALS OF 2^n, n = [0, 10]     ]-----*:. ";
	cout << WHITE << "\n" << message << "\n\n\n";

	output.success = true;
	return output;
}

Message Loading(const int step, const float percentage)
{
	Message output{};

	string message = " *LOADING* : ITERATING IN STEPS OF 2^" + to_string(step) + " : ";
	cout << RED << CLEARLASTLINE << message << percentage << "%" << endl;

	output.success = true;
	return output;
}

Message Done(const int step)
{
	Message output{};

	string message = " *DONE* : ITERATING IN STEPS OF 2^" + to_string(step);
	cout << GREEN << CLEARLASTLINE << message << "\n";

	output.success = true;
	return output;
}

Message AnnounceEnd()
{
	Message output{};

	string message = " .:*-----[     END     ]-----*:. ";
	cout << "\n" << WHITE << message << RESET << "\n\n";

	output.success = true;
	return output;
}

Message PrintTime(const int step, const long long time)
{
	Message output{};

	string message = to_string(step) + " ; " + to_string(time);
	cout << "\n" << YELLOW << message << RESET << "\n";

	output.success = true;
	return output;
}
