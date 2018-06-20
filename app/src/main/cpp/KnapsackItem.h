//
// Created by Jim on 06/05/2018.
//

#ifndef FOODUTILITYOPTIMISER_KNAPSACKITEM_H
#define FOODUTILITYOPTIMISER_KNAPSACKITEM_H

#include <string>

class KnapsackItem
{
public:
    KnapsackItem(const std::string& itemName, int value, int weight);
    ~KnapsackItem();
    std::string getName() const;
    int getWeight() const;
    int getValue() const;

private:
    std::string m_name;
    int m_value;
    int m_weight;
};

#endif //FOODUTILITYOPTIMISER_KNAPSACKITEM_H
