#pragma once

#include <functional>
#include <string>

#include "main.hpp"
#include "AssetLib/structure/VRM/VRMmodelContext.hpp"

namespace VRMQavatars {
    // Stage 1: load / unload a single VRM avatar and place it in front of the player.
    // (Stage 2 adds VRIK, target tracking, blendshapes, springbones back in.)
    class AvatarManager
    {
        public:
        static AssetLib::Structure::VRM::VRMModelContext* currentContext;

        // Starts a coroutine: loads the shader bundle on first use, then the avatar. done(true) on success.
        static void LoadAsync(const std::string& path, std::function<void(bool)> done);

        // Synchronous load (shader must already be resolved).
        static bool LoadNow(const std::string& path);

        static void Unload();

        private:
        static bool bundleTried;
        friend custom_types::Helpers::Coroutine LoadRoutine(std::string, std::function<void(bool)>);
    };
}
