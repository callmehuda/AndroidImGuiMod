#include <thread>
#include <unistd.h>

#include <Obfuscate.h>
#include <Logger.h>
#include <ImGuiHook.h>
#include <BNM/Loading.hpp>

//#define USE_GLM
#include "UnityResolve.hpp"

#include <Offsets.h>
#include <Hooks.h>

#include "JNIHelper.hpp"
#include "xdl.h"

#define ANDROID_MODE 1

// #define ENGINE_UNITY 1

#define OBFS(...) OBFUSCATE(__VA_ARGS__)

/* If i will sell cheat or release to public access
 * 1. Configure OBFUSCATE_BNM in GlobalSettings.hpp
 * 2. Wrap all strings to OBFUSCATE()
 * 3. Update Obfuscate.h
 * 4. Obfuscate cheat library with `oxorany`
 * 5. Library Remap
 */

void load_jni() {
    JNIEnv* env = nullptr;
    for (; !env; usleep(1000))
        env = JNIHelper::GetEnv();

    // if Unity
// #if ENGINE_UNITY
    // if (xdl_open("libunity.so", XDL_TRY_FORCE_LOAD)) {
        // LOGI("load_jni(): Unity engine");
        // BNM::Loading::AllowLateInitHook();
        // //void* handle = dlopen("liblogic.so", RTLD_LAZY);
        // //BNM::Loading::TryLoadByDlfcnHandle(handle);
        // BNM::Loading::TryLoadByJNI(env);
        // BNM::Loading::AddOnLoadedEvent(ofst::Init);
        // BNM::Loading::AddOnLoadedEvent(Setup_Hooks);
    // }
// #endif
    UnityResolve::Init(dlopen("liblogic.so", RTLD_NOW), UnityResolve::Mode::Il2Cpp);
    UnityResolve::ThreadAttach();
    ofst::Init();
    Setup_Hooks();

    LOGI("load_jni(): Initialized %p", env);
    UnityResolve::ThreadDetach();
}

__attribute__((constructor))
void init() {
    std::thread(load_jni).detach();
    std::thread(initMenuHooks).detach();
}
