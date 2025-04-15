# RealityScenes
Tech demo of an OpenGL + SDL + C++ stack built to Meta Quest. Exploration of various OpenGL graphics techniques through interactive, mesmerizing scenes.

## Getting Started with Development

### Install SDL
Git clone the [SDL3 repo](https://github.com/libsdl-org/SDL).

Use cmake to generate a system-specific makefile, but specify that we want both the ARM and Intel versions.
```bash
# Inside the SDL3 source directory
cmake . -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.13 -DSDL_FRAMEWORK=OFF
```
- `-DCMAKE_OSX_ARCHITECTURES`: specifies to build both for ARM and Intel
- `-DCMAKE_OSX_DEPLOYMENT_TARGET`: specifies the minimum macOS version to support
- `-DSDL_FRAMEWORK=OFF`: specifies to build the library as a `.dylib` instead of a Mac `.framework`

At this point, CMake has created a system-specific makefile for us. Now we use `make` to build the library:
```bash
make
# Or, to use multiple threads,
make -j 16
```

Now, we will install the library into `/usr/local/share` (where gcc can find it):
```bash
sudo make install
```

### Install `pkg-config`
`pkg-config` is a tool that simplifies the process of finding library paths to pass to our compilers. Do:

```bash
brew install pkgconf
```

### Set up your Android Environment
You'll need to install the Android NDK, which allows you to run native code in your Android apps. The easiest way to do this is through Android Studio.

### Build the Project
```bash 
make desktop # to build a test version for desktop
make vr # builds for Meta Quest, and installs it to the plugged-in Android device
```

#### Build Details
SDL has its own instructions for compiling to Android. Essentially, the Android NDK allows us to run native C++ code on Android apps. We are using a lightweight Java shim to simply load the native SDL code and application and display it.

- The SDL library is symlinked into the `jni` folder.
- All `.cpp` and `.h` files are copied into `jni/src`.
- The Android project is built like normal using Gradle scripts.

## References
- [SDL Wiki: Android](https://wiki.libsdl.org/SDL3/README/android)
- [SDL Wiki: Building SDL3 for Android](https://wiki.libsdl.org/SDL3/Android)
- [Build D for Android](https://wiki.dlang.org/Build_D_for_Android#Cross-compilation)
- [Cross compiling with LDC](https://wiki.dlang.org/Cross-compiling_with_LDC)
- [LDC confs](https://forum.dlang.org/thread/zxxdcoytocuyxitbwkrn@forum.dlang.org)