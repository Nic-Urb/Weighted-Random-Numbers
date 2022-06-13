// Created by Nicolas Urbanek on 06/13/2022.
// Weighted_RNG_Sys.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Algorithm to define random number from array, for in game use.

#include <iostream>
#include <random>
#include <array>
#include "Weighted_RNG_Sys.h"

using namespace std;

class cWeightedRandomSample
{
public:

    int rand_val;

    // Generate random value from cumulative summary and go through biniary search to find closest element index
    int Choose_Rand(array<int, 3> in_array)
    {
        const int local_sum_of_weight = GetCumulative_Sum(in_array);

        random_device rd;       // Random device, gives some initial randomness to help initialize things. Think of this as the "srand(time())" in the old random(but better)
        mt19937 gen(rd());      // Algorithm to generate the random number. 
        uniform_int_distribution<int> dis(0, local_sum_of_weight);

        rand_val = dis(gen);

        return BiniarySearch(in_array, rand_val);
    }

private:

    int GetCumulative_Sum(array<int, 3> in_array) // Calculate the cumulative value and return the summary
    {
        int local_cumulative_summary = 0;

        for (int i = 0; i < in_array.size(); i++)
        {
            local_cumulative_summary += in_array[i];
        }
        return local_cumulative_summary;
    }
    
    // Do binary search and find closest location element
    int BiniarySearch(array<int, 3> in_array, int in_x)
    {
        int idx_min = 0; // left half
        int idx_max = in_array.size() - 1; // right half

        while (idx_min <= idx_max)
        {
            const int idx_mid = idx_min + (idx_max - idx_min) / 2;

            // check if x is present at mid
            if (in_array[idx_mid] == in_x)
                return idx_mid;

            // if x greater, ignore left half
            if (in_array[idx_mid] < in_x)
                idx_min = idx_mid + 1;

            // if x is smaller, ignore right half
            else
                idx_max = idx_mid - 1;
        }
        // if we're reaching here, then value is higher then last element
        return idx_max;
    }
};

int main()
{
    cWeightedRandomSample* WRD_Ptr = new cWeightedRandomSample(); // Dreate pointer

    // Set up weights
    array<int, 3> weights_array{5, 11, 23};

    const int idx_closestweight = WRD_Ptr->Choose_Rand(weights_array);
    const int rand_val = WRD_Ptr->rand_val;

    // Print result
    cout << "Element location index: " << idx_closestweight << endl;
    cout << "Element value of located index: " << weights_array[idx_closestweight] << endl;
    cout << "Random result value: " << rand_val << endl;


    delete WRD_Ptr; // Delete pointer at the end.
}