#include "Knapsack.h"

Knapsack::Knapsack()
{}

Knapsack::~Knapsack()
{}

std::vector<std::shared_ptr<KnapsackItem>> Knapsack::calculateKnapsack(
        std::vector<std::shared_ptr<KnapsackItem>>& items, int maxWeight)
{
    // TODO Make it less confusing when determining what the current item is
    // TODO Tidy up the code
    // TODO Wrap knapsack in own container
    // TODO Should this be static
    auto nItems = items.size();

    // max + 1 to account for 0 items and 0 weight
    std::vector<std::vector<int>> weightMatrix(nItems + 1, std::vector<int>(maxWeight + 1));

    for (auto currentItem = 1; currentItem <= nItems; ++currentItem)
    {
        for (auto currentWeight = 1; currentWeight <= maxWeight; ++currentWeight)
        {
            // If item won't fit, then get the previous best at the current weight
            if (items[currentItem - 1]->getWeight() > currentWeight)
            {
                weightMatrix[currentItem][currentWeight] = weightMatrix[currentItem - 1][currentWeight];
            }
            else
            {
                // Get the best of either including the item + the previous best we could fit if we included the item, or excluding the item
                auto valueWithCurrentItem = items[currentItem - 1]->getValue() +
                                            weightMatrix[currentItem - 1][currentWeight - items[currentItem - 1]->getWeight()];

                auto previousBest = weightMatrix[currentItem - 1][currentWeight];

                weightMatrix[currentItem][currentWeight] = (valueWithCurrentItem > previousBest) ?
                                                           valueWithCurrentItem : previousBest;
            }
        }
    }

    return getItemsInKnapsack(weightMatrix, items);
}

std::vector<std::shared_ptr<KnapsackItem>> Knapsack::getItemsInKnapsack(std::vector<std::vector<int>>& weightMatrix, std::vector<std::shared_ptr<KnapsackItem>>& items)
{
    // Given the weight matrix, work backwards
    auto nItems = items.size();
    auto currentWeight = weightMatrix.size();
    std::vector<std::shared_ptr<KnapsackItem>> knapsack;

    for (auto currentItem = nItems; currentItem > 0; currentItem--)
    {
        // Need a loop to iterate til currentItem == 0
        if (weightMatrix[currentItem][currentWeight] <= weightMatrix[currentItem - 1][currentWeight])
        {
            // Discard the item
            continue;
        }
        else
        {
            // Add the item, then set currentWeight to be currentWeight -= currentItem->getWeight()
            knapsack.push_back(items.at(currentItem - 1));
            currentWeight -= items.at(currentItem - 1)->getWeight();
        }
    }

    return knapsack;
}