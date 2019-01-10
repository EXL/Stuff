GLFM-example
============

A simple GLFM example for Android.

Additional information:
1. https://www.linux.org.ru/forum/development/14702973
2. https://www.linux.org.ru/forum/development/14721134

## Build and Install (Linux):

```bash
git clone https://github.com/EXLMOTODEV/GLFM-example --recursive
cd GLFM-example/android-project/
ANDROID_HOME="/opt/android-sdk/" ./gradlew assembleDebug
/opt/android-sdk/platform-tools/adb install -r app/build/outputs/apk/debug/app-debug.apk
```
