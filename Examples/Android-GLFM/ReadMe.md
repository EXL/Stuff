Android GLFM Example
====================

A simple GLFM example for Android OS.

Additional information:
1. https://www.linux.org.ru/forum/development/14702973
2. https://www.linux.org.ru/forum/development/14721134

## Build and Install (Linux):

```sh
git clone --recursive --shallow-submodules https://github.com/EXL/Stuff
cd Stuff/Examples/Android-GLFM/android-project/
ANDROID_HOME="/opt/android-sdk/" ./gradlew assembleDebug
/opt/android-sdk/platform-tools/adb install -r app/build/outputs/apk/debug/app-debug.apk
```
