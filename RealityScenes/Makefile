SDL_SOURCE_PATH = ~/Documents/Permanent/SDL3
SOURCES = $(shell find cpp -name '*.cpp' -o -name '*.h')

desktop: cpp-desktop
vr: cpp-vr android-install

cpp-desktop:
	clang $(SOURCES) -o realityscenes-desktop `pkg-config --libs sdl3`
	chmod +x realityscenes-desktop
	./realityscenes-desktop

copy-cpp:
	cp *.cpp android-project/app/jni/src
	cp *.h android-project/app/jni/src

symlink:
	# Link SDL3 source for Android build
	ln -sf $(SDL_SOURCE_PATH) android-project/app/jni

android-build: symlink
	cd android-project && ./gradlew build

android-install: symlink
	cd android-project && ./gradlew installDebug

clean:
	unlink -f android-project/app/jni/SDL3
	rm -f *.o
	rm -f android-project/app/jni/src/*.cpp
	rm -f android-project/app/jni/src/*.h
	rm -f realityscenes-desktop

.PHONY: desktop-development vr-development vr-release clean
