#include "UI/AvatarListViewController.hpp"

#include "main.hpp"
#include "AvatarManager.hpp"
#include "utils/FileUtils.hpp"

#include "bsml/shared/BSML-Lite.hpp"

#include <algorithm>

DEFINE_TYPE(VRMQavatars::UI, AvatarListViewController);

namespace VRMQavatars::UI {

    void AvatarListViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if(!firstActivation) return;

        const auto container = BSML::Lite::CreateScrollableSettingsContainer(get_transform());
        const auto parent = container->get_transform();

        statusText = BSML::Lite::CreateText(parent, "Select a .vrm avatar");

        std::vector<std::string> files;
        GetFilesInFolderPath("vrm", vrm_path, files);
        std::sort(files.begin(), files.end());

        if(files.empty())
        {
            BSML::Lite::CreateText(parent, std::string("No .vrm files found in /") + vrm_path);
        }

        for(const auto& file : files)
        {
            const std::string fullPath = std::string(vrm_path) + "/" + file;
            BSML::Lite::CreateUIButton(parent, file, [this, fullPath, file]() {
                statusText->set_text("Loading " + file + " ...");
                AvatarManager::LoadAsync(fullPath, [this, file](bool ok) {
                    if(statusText) statusText->set_text(ok ? "Loaded " + file : "Failed to load " + file + " (see logcat)");
                });
            });
        }

        BSML::Lite::CreateUIButton(parent, "Unload avatar", [this]() {
            AvatarManager::Unload();
            statusText->set_text("Avatar unloaded");
        });
    }
}
