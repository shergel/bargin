#pragma once

#include <vector>

struct Message
{
	bool success = false;
};

void Init();
void Iterate();
void Deinit();

Message InitStart();
Message InitEnd();
Message AnnounceIterationStart();
Message Loading(const int step, const float percentage);
Message Done(const int step);
Message AnnounceEnd();
Message PrintTime(const int step, const long long time);

/* GLOBAL VARIABLES */
std::vector<int*> g_ints{};
const bool g_debug = false;
const bool g_timer = true;
const int g_amtElements = int(pow(2, 26)); //size of vectors