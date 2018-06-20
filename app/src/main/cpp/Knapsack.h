//
// Created by Jim on 06/05/2018.
//

#ifndef FOODUTILITYOPTIMISER_KNAPSACK_H
#define FOODUTILITYOPTIMISER_KNAPSACK_H

#include "KnapsackItem.h"

#include <memory>
#include <vector>

class Knapsack
{
public:
    Knapsack();
    ~Knapsack();

    std::vector<std::shared_ptr<KnapsackItem>> calculateKnapsack(
            std::vector<std::shared_ptr<KnapsackItem>>& items,
            int maxWeight);

private:
    std::vector<std::shared_ptr<KnapsackItem>> getItemsInKnapsack(
            std::vector<std::vector<int>>& weightMatrix,
            std::vector<std::shared_ptr<KnapsackItem>>& items);
};

#endif //FOODUTILITYOPTIMISER_KNAPSACK_H
