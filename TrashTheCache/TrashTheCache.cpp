using namespace std;
#pragma region head
#include "TrashTheCache.h"
#include "GameObject3D.h"
#include "GameObject3DAlt.h"
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

/* OPTIONAL : PUT g_debug TO FALSE IN ORDER TO TURN OFF LOADING PERCENTAGES/OPTIMIZE*/
int main()
{
	switch (g_typestate) 
	{
	case TypeState::integers:
		InitIntegers();
		IterateIntegers();
		DeinitIntegers();
		break;

	case TypeState::objects:
		InitObjects();
		IterateObjects();
		DeinitObjects();
		break;

	case TypeState::alternatives:
		InitAlternatives();
		IterateAlternatives();
		DeinitAlternatives();
		break;
	}

	std::cin.get();
}

#pragma region messages
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
Message PrintTime(const int step, const long long time)
{
	Message output{};

	string message = to_string(step) + " ; " + to_string(time);
	string buffer = (g_debug) ? "\n" : "";
	cout << "\n" << YELLOW << message << RESET << buffer;

	output.success = true;
	return output;
}
Message AnnounceEnd()
{
	Message output{};

	string message = " .:*-----[     END OF ITERATION     ]-----*:. ";
	cout << "\n" << WHITE << message << RESET << "\n\n";

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
#pragma endregion

#pragma region integers
void InitIntegers()
{
	Message message{};
	if (g_timer || g_debug) message = InitStart();

	for (int i{}; i < g_amtElements; ++i)
	{
		int* element = new int(1);
		g_ints.push_back(element);
	}

	if (g_timer || g_debug) message = InitEnd();
}
void IterateIntegers()
{
	/*debug*/
	Message message{};

	if (g_timer || g_debug) message = AnnounceIterationStart();
	cout << setprecision(2) << fixed;
	float percentage{};
	float percentage_prev = percentage;

	/*times*/
	chrono::steady_clock::time_point start{};
	chrono::steady_clock::time_point end{};
	long long time_delta{};

	/*calc*/
	int step{};

	for (int i{}; i <= g_maxPower; ++i)
	{
		step = int(pow(2, i));

		if (g_timer) start = chrono::high_resolution_clock::now();
		for (int j{}; j < g_amtElements; j += step)
		{
			/* calc */
			percentage = float(j) / g_amtElements * 100;
			*g_ints.at(j) += 20;

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
	if (g_timer || g_debug) message = AnnounceEnd();

} // This 
void DeinitIntegers()
{
	for (int* element : g_ints)
	{
		delete element;
		element = nullptr;
	}
}
#pragma endregion

#pragma region gameobject3d
void InitObjects()
{
	Message message = InitStart();

	for (int i = 0; i < g_amtElements; ++i)
	{
		GameObject3D* element = new GameObject3D();
		g_objects.push_back(element);
	}

	message = InitEnd();
}
void IterateObjects()
{
	/*debug*/
	Message message{};
	if (g_timer || g_debug) AnnounceIterationStart();
	cout << setprecision(2) << fixed;
	float percentage{};
	float percentage_prev = percentage;

	/*times*/
	chrono::steady_clock::time_point start{};
	chrono::steady_clock::time_point end{};
	long long time_delta{};

	/*calc*/
	int step{};

	for (int i{}; i <= g_maxPower; ++i)
	{
		step = int(pow(2, i));

		if (g_timer) start = chrono::high_resolution_clock::now();
		for (int j{}; j < g_amtElements; j += step)
		{
			/* calc */
			percentage = float(j) / g_amtElements * 100;
			g_objects.at(j)->ID += 20;

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
	if (g_timer || g_debug) message = AnnounceEnd();

} // This 
void DeinitObjects()
{
	for (GameObject3D* element : g_objects)
	{
		delete element;
		element = nullptr;
	}
} //todo
#pragma endregion

#pragma region gameobject3dalt
void InitAlternatives()
{
	Message message = InitStart();

	for (int i = 0; i < g_amtElements; ++i)
	{
		GameObject3DAlt* element = new GameObject3DAlt();
		g_alts.push_back(element);
	}

	message = InitEnd();
}
void IterateAlternatives()
{
	/*debug*/
	Message message{};
	if (g_timer || g_debug) AnnounceIterationStart();
	cout << setprecision(2) << fixed;
	float percentage{};
	float percentage_prev = percentage;

	/*times*/
	chrono::steady_clock::time_point start{};
	chrono::steady_clock::time_point end{};
	long long time_delta{};

	/*calc*/
	int step{};

	for (int i{}; i <= g_maxPower; ++i)
	{
		step = int(pow(2, i));

		if (g_timer) start = chrono::high_resolution_clock::now();
		for (int j{}; j < g_amtElements; j += step)
		{
			/* calc */
			percentage = float(j) / g_amtElements * 100;
			g_alts.at(j)->ID += 20;

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
	if (g_timer || g_debug) message = AnnounceEnd();

} // This 
void DeinitAlternatives()
{
	for (GameObject3DAlt* element : g_alts)
	{
		delete element;
		element = nullptr;
	}
} //todo
#pragma endregion