# VRM Qavatars -> Beat Saber 1.40.8_7379 port (STEP 1, NOT COMPILED)

Done in step 1:
- qpm.json rewritten (beatsaber-hook ^6.4.2, bs-cordl 4008.*, custom-types ^0.18.3,
  scotland2 ^0.1.6, paper2_scotland2 ^4.6.4, bsml ^0.4.55, chatplex-sdk-bs ^6.4.1).
  questui / codegen / modloader removed. Old qpm.shared.json deleted (qpm restore regenerates it).
- mod.template.json: modloader Scotland2, packageVersion 1.40.8_7379.
- CMakeLists.txt: removed the old codegen include line.
- include/main.hpp: scotland2 + Paper logger, plus a printf-style getLogger() shim
  so the ~100 existing getLogger().info("...%d") calls keep compiling.
- include/config/mini-config-utils.hpp: no longer depends on the old Logger/ModInfo.
- src/main.cpp: new entry points (setup(CModInfo*) / late_load), BSML::Init, hooks use PaperLogger.

Known risks (verify when building):
- Hook targets may have changed in 1.40.8: Saber::ManualUpdate, MainEffectContainerSO::Init
  (get_hasPostProcessEffect), MainCamera::Awake.
- assets_include.cmake builds an Il2CppArray header by hand (the "33" offset); compare it with
  the current Quest-Mod-Template version.
- Step 3 (UI): src/UI/*.cpp and include/AssetLib/arrayUtils.hpp still use QuestUI
  (CreateViewController, ArrayToSprite, GetMainTextFont...). They will fail until ported to BSML.
- Many files use old codegen headers/APIs; expect compile errors to fix file by file.
- chatplex-sdk-bs macros (CP_SDK_IL2CPP_DECLARE_CTOR*) may need the 6.4.x equivalents.
