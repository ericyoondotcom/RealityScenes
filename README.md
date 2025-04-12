# RealityScenes
Tech demo of an OpenGL + SDL + Dlang stack built to Meta Quest. Exploration of various OpenGL graphics techniques through interactive, mesmerizing scenes.

## Getting Started with Development

### Install SDL
Instructions WIP, but basically the same process as for RhythmGameStudio

### Set up your Android Environment
You'll need to install the Android NDK, which allows you to run native code in your Android apps. The easiest way to do this is through Android Studio.

### Set up the Android Cross Compilation
We have to use LDC, along with a prebuilt Android package, to cross-compile Dlang to Android.

We've set up an Android project (`android-project`), which has Gradle scripts. 

## References
- [SDL Wiki: Android](https://wiki.libsdl.org/SDL3/README/android)
- [SDL Wiki: Building SDL3 for Android](https://wiki.libsdl.org/SDL3/Android)
- [Build D for Android](https://wiki.dlang.org/Build_D_for_Android#Cross-compilation)
