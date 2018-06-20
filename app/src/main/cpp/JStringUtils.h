//
// Created by Jim on 28/05/2018.
//

#ifndef FOODUTILITYOPTIMISER_JSTRINGUTILS_H
#define FOODUTILITYOPTIMISER_JSTRINGUTILS_H

#include <string>
#include <sstream>
#include <jni.h>
#include <vector>

class JStringUtils
{
public:
    static std::string jstringToString(JNIEnv* env, jstring jStr)
    {
        if (!jStr)
            return "";

        const jclass stringClass = env->GetObjectClass(jStr);
        const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
        const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

        size_t length = (size_t) env->GetArrayLength(stringJbytes);
        jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

        std::string ret = std::string((char *)pBytes, length);
        env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

        env->DeleteLocalRef(stringJbytes);
        env->DeleteLocalRef(stringClass);
        return ret;
    };

    static jstring concatJstrings(JNIEnv *env, const std::vector<jstring>& strings)
    {
        std::ostringstream oss;
        for (auto it = strings.begin(); it != strings.end(); ++it)
        {
            oss << jstringToString(env, *it);
        }

        auto out = oss.str().c_str();
        return env->NewStringUTF(out);
    };
};
#endif //FOODUTILITYOPTIMISER_JSTRINGUTILS_H
