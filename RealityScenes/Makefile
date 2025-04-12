SDL_SOURCE_PATH = ~/Documents/Permanent/SDL3

SOURCES = $(shell find source -name '*.d')

desktop-development: dlang-desktop-development
vr-development: android-development
vr-release: android-release

dlang-desktop-development:
	dub run --build=desktop-development
dlang-vr-development:
	dub build --build=vr-development
dlang-vr-release:
	dub build --build=vr-release

android:
	ln -s $(SDL_SOURCE_PATH) android-project/app/jni