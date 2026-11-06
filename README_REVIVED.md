# VRM Qavatars Revived (Beat Saber 1.40.8_7379)

STAGE 1 (this build): VRM loading + BSML menu entry "VRM Qavatars".
 - Put .vrm files in /sdcard/ModData/com.beatgames.beatsaber/Mods/VRMQavatars/Avatars
 - Main menu -> "VRM Qavatars" -> pick a file -> avatar appears 1.5 m in front of you (static, no IK yet).
 - Not compiled yet. Fix build errors file by file.

Later stages (original code kept untouched in _later/, to be ported one by one):
 - STAGE 2: VRIK + TargetManager + calibration, blendshapes, springbones, wrist twist, wind, T-pose
 - STAGE 3: settings UI (BSML), mirror, lighting, VMC, lipsync, hand poses
 To enable a stage: move files from _later/ back into src/ + include/ and raise VRMQ_STAGE in CMakeLists.txt.

Risks to check first:
 - shaders.sbund was built for an old Unity; if it won't load, the fallback shader (Sprites/Default) is used (no toon shading).
 - BSML include paths (BSML-Lite.hpp, Helpers/creation.hpp, BSML/SharedCoroutineStarter.hpp) may differ in bsml 0.4.55.
 - Hook-free build: no game classes are hooked in stage 1.

## Making the .qmod
After the build produces libvrm-qavatars.so (build/ folder or the Actions artifact):
    bash qmod_kit/make_qmod.sh                # auto-finds build/libvrm-qavatars.so
    bash qmod_kit/make_qmod.sh path/to/libvrm-qavatars.so
-> VRM_Qavatars_Revived_1.40.8.qmod (mod.json + .so + shaders.sbund). Install it with MBF.


## Build on GitHub (no PC needed)
This repo is self-contained: .github/workflows/build.yml builds it (no template repo needed).
 1. Create an empty repo on github.com, open a Codespace, upload the zip.
 2. unzip, cp -r revived/. ., git add -A, git commit, git push.
 3. Actions tab -> latest run -> Artifacts: VRM_Qavatars_Revived_qmod / libvrm-qavatars_so / build-logs.
