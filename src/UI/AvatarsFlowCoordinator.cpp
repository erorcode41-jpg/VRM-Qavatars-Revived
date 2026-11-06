#include "UI/AvatarsFlowCoordinator.hpp"

#include "main.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/creation.hpp"

DEFINE_TYPE(VRMQavatars::UI, AvatarsFlowCoordinator);

namespace VRMQavatars::UI {

    void AvatarsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if(!firstActivation) return;

        if(!listViewController)
        {
            listViewController = BSML::Helpers::CreateViewController<AvatarListViewController*>();
        }

        SetTitle("VRM Qavatars", HMUI::ViewController::AnimationType::In);
        showBackButton = true;
        ProvideInitialViewControllers(listViewController, nullptr, nullptr, nullptr, nullptr);
    }

    void AvatarsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        _parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}
