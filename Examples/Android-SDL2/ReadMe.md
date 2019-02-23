SDL2-Android-Example
====================

A simple SDL2 example for Android.

## Build and Install (Linux):

```bash
git clone https://github.com/EXLMOTODEV/SDL2-Android-Example --recursive --shallow-submodules
cd SDL2-Android-Example/
ANDROID_HOME="/opt/android-sdk/" ./gradlew assembleDebug
<connect your smartphone>
/opt/android-sdk/platform-tools/adb install -r app/build/outputs/apk/debug/app-debug.apk

```

Thanks for the example to @suikki (Olli Kallioinen).
