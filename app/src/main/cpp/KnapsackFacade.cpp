//
// Created by Jim on 07/05/2018.
//

#include <jni.h>
#include <vector>
#include <memory>
#include "JStringUtils.h"
#include "KnapsackItem.h"
#include "StringUtils.h"
#include "Knapsack.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_jimfkong_foodutilityoptimiser_Knapsack_GetHelloWorldString(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF("Hello with jstring");
}

// TODO Fob most of this into a KnapsackService

enum KnapsackItemIdx {
    name = 0,
    value = 1,
    weight = 2
};

std::shared_ptr<KnapsackItem> GenerateKnapsackItem(JNIEnv* env, const jstring& itemCSV)
{
    auto parts = StringUtils::splitString(JStringUtils::jstringToString(env, itemCSV), ',');
    return std::make_shared<KnapsackItem>(
            parts[KnapsackItemIdx::name],
            std::stoi(parts[KnapsackItemIdx::value]),
            std::stoi(parts[KnapsackItemIdx::weight])
    );
}

std::vector<std::shared_ptr<KnapsackItem>> GetItemsFromRequest(JNIEnv* env,
                                                               const jobject& knapsackRequest)
{
    auto request = env->GetObjectClass(knapsackRequest);
    auto itemsLabel = env->GetFieldID(request, "items", "[Ljava/lang/String;");
    auto items = (jobjectArray)env->GetObjectField(knapsackRequest, itemsLabel);
    std::vector<std::shared_ptr<KnapsackItem>> knapsackItems;

    auto itemsCount = env->GetArrayLength(items);

    for (int i = 0; i < itemsCount; i++)
    {
        auto line = (jstring) (env->GetObjectArrayElement(items, i));
        knapsackItems.push_back(GenerateKnapsackItem(env, line));
    }

    return knapsackItems;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_jimfkong_foodutilityoptimiser_Knapsack_PassKotlinObject(JNIEnv* env,
                                                                 jobject instance,
                                                                 jobject knapsackRequest) {
    auto request = env->GetObjectClass(knapsackRequest);
    auto maxWeightID = env->GetFieldID(request, "maxWeight", "I");

    auto maxWeight = env->GetIntField(knapsackRequest, maxWeightID);
    auto items = GetItemsFromRequest(env, knapsackRequest);

    Knapsack knapsackAlgo;
    auto result = knapsackAlgo.calculateKnapsack(items, maxWeight);

    std::ostringstream oss;

    for (auto it = result.begin(); it != result.end(); ++it)
    {
        oss << it->get()->getName() << ",";
    }

    auto resultString = oss.str();

    return env->NewStringUTF(resultString.substr(0, resultString.length() - 1).c_str());

//    auto jStringArray = (jobjectArray)env->NewObjectArray(
//            result.size(),
//            env->FindClass("java/lang/String"),
//            env->NewStringUTF("")
//    );
//
//    for (auto i = 0; i < 2; i++)
//    {
//        env->SetObjectArrayElement(
//                jStringArray,
//                i,
//                env->NewStringUTF(result[i]->getName().c_str())
//        );
//    }

//    auto returnClass = env->FindClass("com/jimfkong/foodutilityoptimiser/KnapsackResponse");
//    auto methodID = env->GetMethodID(returnClass, "<init>", "([java/lang/String)V");

//    return env->NewStringUTF("foobar");
}

