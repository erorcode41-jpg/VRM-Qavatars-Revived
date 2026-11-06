#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(VRMQavatars::UI, AvatarListViewController, HMUI::ViewController) {
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, statusText);

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
};
