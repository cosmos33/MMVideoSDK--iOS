#ifndef __ANDROID_XAUDIO_JNI_HELPER_H__
#define __ANDROID_XAUDIO_JNI_HELPER_H__

#ifdef X_PLATFORM_ANDROID

#include <jni.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include <android/log.h>

#define  LOG_TAG    "XAudioJniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef struct XAudioJniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} XAudioJniMethodInfo;

bool UTF16ToUTF8(const std::u16string &inUtf16, std::string &outUtf8);
std::string utf16le_to_utf8(const std::u16string &u16str);
std::string utf16be_to_utf8(const std::u16string &u16str);
std::u16string utf8_to_utf16le(const std::string &u8str, bool addbom, bool ok);
bool UTF8ToUTF16(const std::string &inUtf8, std::u16string &outUtf16);
std::string getStringUTFCharsJNI(JNIEnv *env, jstring srcjStr, bool *ret = nullptr);
jstring newStringUTFJNI(JNIEnv *env, const std::string &utf8Str, bool *ret = nullptr);

class XAudioJniHelper
{
public:
    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static jobject getActivity();

    static bool setClassLoaderFrom(jobject activityInstance, jobject classLoader);
	static bool getStaticMethodInfo(XAudioJniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode);
	static bool getMethodInfo(XAudioJniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode);

    static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;
    static std::function<void()> classloaderCallback;

    template <typename... Ts>
    static void callStaticVoidMethod(const std::string& className, 
                                     const std::string& methodName, 
                                     Ts... xs) {
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        }
        else
        {
            reportError(className, methodName, signature);
        }
    }

    template <typename... Ts>
    static bool callStaticBooleanMethod(const std::string& className, 
                                        const std::string& methodName, 
                                        Ts... xs) {
        jboolean jret = JNI_FALSE;
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            jret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return (jret == JNI_TRUE);
    }

    template <typename... Ts>
    static int callStaticIntMethod(const std::string& className, 
                                   const std::string& methodName, 
                                   Ts... xs) {
        jint ret = 0;
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")I";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            ret = t.env->CallStaticIntMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static float callStaticFloatMethod(const std::string& className, 
                                       const std::string& methodName, 
                                       Ts... xs) {
        jfloat ret = 0.0;
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")F";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static float* callStaticFloatArrayMethod(const std::string& className, 
                                       const std::string& methodName, 
                                       Ts... xs) {
        static float ret[32];
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")[F";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            jfloatArray array = (jfloatArray) t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(t, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len <= 32) {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                if (elems) {
                    memcpy(ret, elems, sizeof(float) * len);
                    t.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
            return &ret[0];
        } else {
            reportError(className, methodName, signature);
        }
        return nullptr;
    }

    template <typename... Ts>
    static double callStaticDoubleMethod(const std::string& className, 
                                         const std::string& methodName, 
                                         Ts... xs) {
        jdouble ret = 0.0;
		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")D";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static std::string callStaticStringMethod(const std::string& className, 
                                              const std::string& methodName, 
                                              Ts... xs) {
        std::string ret;

		XAudioJniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
		if (XAudioJniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            //jclass classXUIEditBoxHelper = t.env->GetObjectClass(g_JNIEditBoxHelperObject);
            jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(t, xs)...);
            ret = XAudioJniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

	static bool getMethodInfo_DefaultClassLoader(XAudioJniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);

    static JavaVM* _psJavaVM;
    
    static jobject _activity;

	static jstring convert(XAudioJniMethodInfo& t, const char* x);

	static jstring convert(XAudioJniMethodInfo& t, const std::string& x);

    template <typename T>
	static T convert(XAudioJniMethodInfo&, T x) {
        return x;
    }

    static std::unordered_map<JNIEnv*, std::vector<jobject>> localRefs;

    static void deleteLocalRefs(JNIEnv* env);

    static std::string getJNISignature() {
        return "";
    }

    static std::string getJNISignature(bool) {
        return "Z";
    }

    static std::string getJNISignature(char) {
        return "C";
    }

    static std::string getJNISignature(short) {
        return "S";
    }

    static std::string getJNISignature(int) {
        return "I";
    }

    static std::string getJNISignature(long) {
        return "J";
    }

    static std::string getJNISignature(float) {
        return "F";
    }

   static  std::string getJNISignature(double) {
        return "D";
    }

    static std::string getJNISignature(const char*) {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(const std::string&) {
        return "Ljava/lang/String;";
    }

    template <typename T>
    static std::string getJNISignature(T x) {
        // This template should never be instantiated
        //static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }

    template <typename T, typename... Ts>
    static std::string getJNISignature(T x, Ts... xs) {
        return getJNISignature(x) + getJNISignature(xs...);
    }

    static void reportError(const std::string& className, const std::string& methodName, const std::string& signature);
};

#endif

#endif // __ANDROID_XAUDIO_JNI_HELPER_H__
