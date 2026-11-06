#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

#include "UI/AvatarListViewController.hpp"

DECLARE_CLASS_CODEGEN(VRMQavatars::UI, AvatarsFlowCoordinator, HMUI::FlowCoordinator) {
    DECLARE_INSTANCE_FIELD(VRMQavatars::UI::AvatarListViewController*, listViewController);

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::FlowCoordinator::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, BackButtonWasPressed, &HMUI::FlowCoordinator::BackButtonWasPressed, HMUI::ViewController* topViewController);
};
