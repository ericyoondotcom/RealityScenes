SDL_SOURCE_PATH = ~/Documents/Permanent/SDL3

SOURCES = $(shell find source -name '*.d')

desktop-development: dlang-desktop-development
vr-development: dlang-vr-development android-install
vr-release: dlang-vr-release android-install

dlang-desktop-development:
	dub run --build=desktop-development
dlang-vr-development:
	ldc2 -mtriple=aarch64--linux-android29 $(SOURCES)
dlang-vr-release:
	dub build --build=vr-release

symlink:
	# Link SDL3 source for Android build
	ln -sf $(SDL_SOURCE_PATH) android-project/app/jni

android-build: symlink
	cd android-project && ./gradlew build

android-install: symlink
	cd android-project && ./gradlew installDebug

clean:
	unlink -f android-project/app/jni/SDL3
	rm realityscenes

.PHONY: desktop-development vr-development vr-release clean
