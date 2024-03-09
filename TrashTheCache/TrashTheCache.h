#pragma once

#include <vector>
class GameObject3D;

struct Message
{
	bool success = false;
};

enum class TypeState
{
	integers = 0,
	objects = 1
};

void InitIntegers();
void IterateIntegers();
void DeinitIntegers();

void InitObjects();
void IterateObjects();
void DeinitObjects();

Message InitStart();
Message InitEnd();
Message AnnounceIterationStart();
Message Loading(const int step, const float percentage);
Message Done(const int step);
Message AnnounceEnd();
Message PrintTime(const int step, const long long time);

/* GLOBAL VARIABLES */
std::vector<int*> g_ints{};
std::vector<GameObject3D*> g_objects{};
const int g_maxPower = 10;
const int g_amtElements = int(pow(2, 26)); //size of vectors

const bool g_debug = false;
const bool g_timer = true;
TypeState g_typestate = TypeState::objects;
