package com.jimfkong.foodutilityoptimiser

class Knapsack {
    init {
        System.loadLibrary("knapsack")
    }

    external fun PassKotlinObject(request: KnapsackRequest): String
}