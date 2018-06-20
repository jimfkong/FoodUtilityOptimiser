#include "KnapsackItem.h"

KnapsackItem::KnapsackItem(const std::string& itemName, int value, int weight) :
        m_name(itemName), m_value(value), m_weight(weight)
{}

KnapsackItem::~KnapsackItem() {}

std::string KnapsackItem::getName() const
{
    return m_name;
}

int KnapsackItem::getWeight() const
{
    return m_weight;
}

int KnapsackItem::getValue() const
{
    return m_value;
}