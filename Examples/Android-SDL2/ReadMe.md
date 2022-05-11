Android SDL2 Example
====================

A simple SDL2 example for Android.

## Build, Install and Run on Android:

```bash
git clone https://github.com/EXL/Stuff
cd Stuff/Examples/Android-SDL2/
git submodule update --init --depth=1 app/jni/SDL
ANDROID_HOME="/opt/android-sdk/" ./gradlew assembleDebug

<connect your smartphone>

/opt/android-sdk/platform-tools/adb install -r app/build/outputs/apk/debug/app-debug.apk
/opt/android-sdk/platform-tools/adb shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity
```

Thanks for the [simpleSDL](https://github.com/suikki/simpleSDL) example to @[suikki](https://github.com/suikki) (Olli Kallioinen).
