#include "AvatarManager.hpp"

#include <filesystem>

#include "custom-types/shared/coroutine.hpp"
#include "bsml/shared/BSML/SharedCoroutineStarter.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"

#include "AssetLib/modelImporter.hpp"
#include "AssetLib/shaders/shaderLoader.hpp"

namespace VRMQavatars {

    AssetLib::Structure::VRM::VRMModelContext* AvatarManager::currentContext = nullptr;
    bool AvatarManager::bundleTried = false;

    void AvatarManager::Unload()
    {
        if(currentContext == nullptr) return;
        if(currentContext->rootGameObject)
        {
            UnityEngine::Object::Destroy(currentContext->rootGameObject);
        }
        delete currentContext;
        currentContext = nullptr;
    }

    bool AvatarManager::LoadNow(const std::string& path)
    {
        Unload();

        if(!std::filesystem::exists(path))
        {
            getLogger().error("VRM file does not exist: %s", path.c_str());
            return false;
        }

        // Preferred: MToon shader from shaders.sbund. Fallback: a built-in unlit textured shader,
        // so the avatar still shows up if the old bundle can't be loaded on this Unity version.
        UnityEngine::Shader* shader = AssetLib::ModelImporter::mtoon.ptr();
        if(!shader)
        {
            getLogger().info("MToon bundle not available, using fallback shader");
            shader = UnityEngine::Shader::Find("Sprites/Default");
        }
        if(!shader)
        {
            getLogger().error("No usable shader found");
            return false;
        }

        try
        {
            currentContext = AssetLib::ModelImporter::LoadVRM(path, shader);
        }
        catch(const std::exception& e)
        {
            getLogger().error("Failed to load VRM: %s", e.what());
            currentContext = nullptr;
            return false;
        }

        if(currentContext == nullptr || currentContext->rootGameObject == nullptr) return false;

        // Put the avatar 1.5m in front of the origin, turned to face the player.
        const auto tr = currentContext->rootGameObject->get_transform();
        tr->set_position(UnityEngine::Vector3(0.0f, 0.0f, 1.5f));
        tr->set_rotation(UnityEngine::Quaternion::Euler(0.0f, 180.0f, 0.0f));
        return true;
    }

    custom_types::Helpers::Coroutine LoadRoutine(std::string path, std::function<void(bool)> done)
    {
        if(!AvatarManager::bundleTried && !AssetLib::ModelImporter::mtoon)
        {
            AvatarManager::bundleTried = true;
            co_yield custom_types::Helpers::CoroutineHelper::New(ShaderLoader::LoadBund());
        }
        const bool ok = AvatarManager::LoadNow(path);
        if(done) done(ok);
        co_return;
    }

    void AvatarManager::LoadAsync(const std::string& path, std::function<void(bool)> done)
    {
        BSML::SharedCoroutineStarter::get_instance()->StartCoroutine(
            custom_types::Helpers::CoroutineHelper::New(LoadRoutine(path, std::move(done))));
    }
}
