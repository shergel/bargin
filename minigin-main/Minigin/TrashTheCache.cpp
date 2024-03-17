#include "TrashTheCache.h"
#include <vector>


using namespace bgn;

std::vector<float> TrashTheCache::GetAveragesInts(const int samples)
{
	if (m_previousSamples != samples || m_integers.size() == 0)
	{
		DeinitObjects(m_integers);
		InitObjects(m_integers);
	}
	m_previousSamples = samples;

	return  CalculateAvgTimes_INT(m_integers, samples);
}
std::vector<float> TrashTheCache::GetAveragesGameObject3Ds(const int samples)
{
	if (m_previousSamples != samples || m_gameobject3ds.size() == 0)
	{
		DeinitObjects(m_gameobject3ds);
		InitObjects(m_gameobject3ds);
	}

	m_previousSamples = samples;
	return CalculateAverageTimes_MEMBERINT(m_gameobject3ds, &GameObject3D::ID, samples);
}
std::vector<float> TrashTheCache::GetAveragesGameObject3DAlts(const int samples)
{
	if (m_previousSamples != samples || m_gameobject3dalts.size() == 0)
	{
		DeinitObjects(m_gameobject3dalts);
		InitObjects(m_gameobject3dalts);
	}

	m_previousSamples = samples;
	return CalculateAverageTimes_MEMBERINT(m_gameobject3dalts, &GameObject3DAlt::ID, samples);

}

const std::vector<float> TrashTheCache::CalculateAvgTimes_INT(const std::vector<int*>& ints, const int samples)
{
	std::vector<long long> times;
	std::vector<float> averages;

	for (int i = 0; i <= m_maxPower; ++i) {
		int step = int(pow(2, i));

		// Loop through each sample
		for (int smp = 0; smp < samples; ++smp) {
			auto start = std::chrono::high_resolution_clock::now();
			for (int j = 0; j < (int)ints.size(); j += step)
			{
				*ints.at(j) += 20;
			}
			auto end = std::chrono::high_resolution_clock::now();
			long long time_delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			// Store time
			times.push_back(time_delta);
		}
		// Remove outliers
		std::sort(times.begin(), times.end());
		if (samples >= 6)
		{
			times.erase(times.begin(), times.begin() + 2); // Removes highest 2
			times.erase(times.end() - 2, times.end()); // Removes lowest two
		}

		// Calculate average time for this iteration
		long long sum = std::accumulate(times.begin(), times.end(), 0LL);
		float average = float(sum / times.size());
		averages.push_back(average);

		times.clear();
	}

	return averages;

}