# RealityScenes
Tech demo of an OpenGL + SDL + Dlang stack built to Meta Quest. Exploration of various OpenGL graphics techniques through interactive, mesmerizing scenes.

## Getting Started with Development

### High-Level Overview
SDL has its own instructions for compiling to Android. Essentially, the Android NDK allows us to run native code on Android apps. We are using a lightweight Java shim to simply load the native SDL code and application and display it.

At the same time, Dlang has its own instructions for cross-compiling to Android. We will be using LDC, a Dlang compiler, to compile the D code to run on Android. This code will then go into the Android JNI folder, where it is interpreted by the NDK and Java shim.

### Install SDL
Instructions WIP, but basically the same process as for RhythmGameStudio

### Set up your Android Environment
You'll need to install the Android NDK, which allows you to run native code in your Android apps. The easiest way to do this is through Android Studio.

### Set up the Android Cross Compilation
We have to use LDC, along with a prebuilt Android package, to cross-compile Dlang to Android. Download the _AArch64_ version of the android package [here](https://github.com/ldc-developers/ldc/releases/). Extract the `lib` directory, and put it somewhere on your system.

LDC2 will respect the `ldc2.conf` file in the CWD, so we've gone ahead and set one up in this project. In the `ldc2.conf` file, please edit the specified paths to your Android NDK path and the extracted ldc2 Android `lib` folder.

We've set up an Android project (`android-project`), which has Gradle scripts.

### How we set up the Android Shim
We followed the instructions [here](https://wiki.libsdl.org/SDL3/README/android) (under "building a more complex app"). We added `assets.srcDirs` to `app/build.gradle` to include assets and shaders.

## TODO
- We could keep trying to fix LDC2 conf file
    - Have to add a bunch of things to `post-switches`?
    ```
    "-I/Users/yooniverse/.dub/packages/bindbc-sdl/2.1.0/bindbc-sdl/source",
    "-I/Users/yooniverse/.dub/packages/bindbc-common/1.0.5/bindbc-common/source",
    ```
- Or we could try to get Dub to cross-compile (see bottom of [Cross compiling with LDC](https://wiki.dlang.org/Cross-compiling_with_LDC))

## References
- [SDL Wiki: Android](https://wiki.libsdl.org/SDL3/README/android)
- [SDL Wiki: Building SDL3 for Android](https://wiki.libsdl.org/SDL3/Android)
- [Build D for Android](https://wiki.dlang.org/Build_D_for_Android#Cross-compilation)
- [Cross compiling with LDC](https://wiki.dlang.org/Cross-compiling_with_LDC)
- [LDC confs](https://forum.dlang.org/thread/zxxdcoytocuyxitbwkrn@forum.dlang.org)