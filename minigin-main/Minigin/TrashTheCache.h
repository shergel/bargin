#pragma once
#include "Singleton.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>  
#include "GameObject3D.h"
#include "GameObject3DAlt.h"

class TrashTheCache final : public bgn::Singleton<TrashTheCache>
{
public:
    ~TrashTheCache()
    {
        DeinitObjects(m_integers);
        DeinitObjects(m_gameobject3ds);
        DeinitObjects(m_gameobject3dalts);
    }

    const int GetDataCount() { return m_maxPower+1; }

    std::vector<float> GetAveragesInts(const int samples);
    std::vector<float> GetAveragesGameObject3Ds(const int samples);
    std::vector<float> GetAveragesGameObject3DAlts(const int samples);

#pragma region Templates
    //Allocate
    template<typename T>
    void InitObjects(std::vector<T*>& objects);
    //Calculate data for OBJECT INTS (eg ID) : average times
    template<typename T, typename MemberType>
    const std::vector<float> CalculateAverageTimes_MEMBERINT(const std::vector<T*>& objects, MemberType T::* member, const int samples = 1);

    //Delete
    template<typename T>
    void DeinitObjects(std::vector<T*>& objects);
#pragma endregion

private:
    std::vector<int*> m_integers{};
    std::vector<GameObject3D*> m_gameobject3ds{};
    std::vector<GameObject3DAlt*> m_gameobject3dalts{};

    //Calculate data for INTS : average times
    const std::vector<float> CalculateAvgTimes_INT(const std::vector<int*>& ints, const int samples = 1);

    static const int m_maxPower = 10;
    const int m_amtElements = int(pow(2, 20));
    int m_previousSamples{ -1 };
};

#pragma region Templates

template<typename T>
void TrashTheCache::InitObjects(std::vector<T*>& objects) {

    for (int i = 0; i < m_amtElements; ++i)
    {
        T* element = new T();
        objects.push_back(element);
    }
}

template<typename T, typename MemberType>
const std::vector<float> TrashTheCache::CalculateAverageTimes_MEMBERINT(const std::vector<T*>& objects, MemberType T::* member, const int samples){

    std::vector<long long> times;
    std::vector<float> averages;

    for (int i = 0; i <= m_maxPower; ++i) {
        int step = int(pow(2, i));

        // Loop through each sample
        for (int smp = 0; smp < samples; ++smp) {
            auto start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < (int)objects.size(); j += step)
            {
               (objects.at(j)->*member) += 20;
            }
            auto end = std::chrono::high_resolution_clock::now();
            long long time_delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Store time
            times.push_back(time_delta);
        }
        // Remove outliers
        std::sort(times.begin(), times.end());
        /*if (samples >= 6)
        {*/
            times.erase(times.begin(), times.begin() + 2); // Removes highest 2
            times.erase(times.end() - 2, times.end()); // Removes lowest two
        /*}*/
       

        // Calculate average time for this iteration
        long long sum = std::accumulate(times.begin(), times.end(), 0LL);
        float average = float(sum / times.size());
        averages.push_back(average);

        times.clear();
    }

    return averages;
}

template<typename T>
void TrashTheCache::DeinitObjects(std::vector<T*>& objects) {
       
    for (T* element : objects) {
        delete element;
        element = nullptr;
    }
     
    objects.clear();
}
#pragma endregion
