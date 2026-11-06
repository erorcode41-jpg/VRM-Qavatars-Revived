#include "main.hpp"

#include "bsml/shared/BSML.hpp"
#include "custom-types/shared/register.hpp"

#include <filesystem>

#include "UI/AvatarsFlowCoordinator.hpp"
#include "config/ConfigManager.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

MOD_EXTERN_FUNC void setup(CModInfo* info) noexcept {
    *info = modInfo.to_c();

    Paper::Logger::RegisterFileContextId(PaperLogger.tag);
    getLogger().info("VRM Qavatars Revived (stage %d) setup", VRMQ_STAGE);

    // same location the old Configuration::getConfigFilePath() produced
    getGlobalConfig().Init("/sdcard/ModData/com.beatgames.beatsaber/Configs/" MOD_ID ".json");
}

MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    std::filesystem::create_directories(std::string("/") + vrm_path);
    std::filesystem::create_directories(std::string("/") + avaconfig_path);

    custom_types::Register::AutoRegister();

    BSML::Init();
    BSML::Register::RegisterMainMenu<VRMQavatars::UI::AvatarsFlowCoordinator*>("VRM Qavatars", "Load a VRM avatar");

    getLogger().info("VRM Qavatars Revived loaded");
}
