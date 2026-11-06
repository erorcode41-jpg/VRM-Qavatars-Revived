#pragma once

#include "scotland2/shared/modloader.h"
#include "paper2_scotland2/shared/logger.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include <android/log.h>
#include <cstdio>

// Logger used by INSTALL_HOOK
constexpr auto PaperLogger = Paper::ConstLoggerContext(MOD_ID);

// Compatibility shim: the original code base has ~100 printf-style calls of the form
// getLogger().info("...%d", x) / getLogger().error(...). Old beatsaber-hook's Logger is gone,
// so these are forwarded to logcat with the same printf semantics.
struct LegacyLogger {
    template<typename... Args>
    void info(const char* fmt, Args... args) const {
        char buf[2048];
        snprintf(buf, sizeof(buf), fmt, args...);
        __android_log_print(ANDROID_LOG_INFO, MOD_ID, "%s", buf);
    }
    template<typename... Args>
    void error(const char* fmt, Args... args) const {
        char buf[2048];
        snprintf(buf, sizeof(buf), fmt, args...);
        __android_log_print(ANDROID_LOG_ERROR, MOD_ID, "%s", buf);
    }
};
inline const LegacyLogger& getLogger() {
    static const LegacyLogger l;
    return l;
}

#ifndef GET_FIND_METHOD
#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()
#endif

constexpr const char* vrm_path = "sdcard/ModData/com.beatgames.beatsaber/Mods/VRMQavatars/Avatars";
// NOTE: paths are relative to "/" on Android (kept from the original). Use std::string("/") + vrm_path where an absolute path is needed.
constexpr const char* avaconfig_path = "sdcard/ModData/com.beatgames.beatsaber/Mods/VRMQavatars/AvatarConfigs/";
