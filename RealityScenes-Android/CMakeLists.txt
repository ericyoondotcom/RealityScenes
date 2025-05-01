cmake_minimum_required(VERSION 3.22.1)
set(PROJECT_NAME RealityScenes)
project("${PROJECT_NAME}")








# Additional Directories for find_package() to search within.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# For FetchContent_Declare() and FetchContent_MakeAvailable()
include(FetchContent)







# openxr_loader - From github.com/KhronosGroup
set(BUILD_TESTS
        OFF
        CACHE INTERNAL "Build tests"
)
set(BUILD_API_LAYERS
        ON
        CACHE INTERNAL "Use OpenXR layers"
)
FetchContent_Declare(
        OpenXR
        URL_HASH MD5=924a94a2da0b5ef8e82154c623d88644
        URL https://github.com/KhronosGroup/OpenXR-SDK-Source/archive/refs/tags/release-1.0.34.zip
        SOURCE_DIR
        openxr
)
FetchContent_MakeAvailable(OpenXR)








# Files
set(SOURCES
        "main.cpp"
        "ey_scene.cpp"
        "ey_shared.cpp"
        "../Common/GraphicsAPI.cpp"
        "../Common/GraphicsAPI_OpenGL_ES.cpp"
        "../Common/OpenXRDebugUtils.cpp")
set(HEADERS
        "ey_scene.h"
        "ey_shared.h"
        "../Common/DebugOutput.h"
        "../Common/GraphicsAPI.h"
        "../Common/GraphicsAPI_OpenGL_ES.h"
        "../Common/HelperFunctions.h"
        "../Common/OpenXRDebugUtils.h"
        "../Common/OpenXRHelper.h"
        "../Common/xr_linear_algebra.h")




add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        # In this repo
        "../Common/"
        # From OpenXR repo
        "${openxr_SOURCE_DIR}/src/common"
        "${openxr_SOURCE_DIR}/external/include"
)

# export ANativeActivity_onCreate for java to call.
set_property(
        TARGET ${PROJECT_NAME}
        APPEND_STRING
        PROPERTY LINK_FLAGS " -u ANativeActivity_onCreate"
)

# native_app_glue
include(AndroidNdkModules)
android_ndk_import_module_native_app_glue()

target_link_libraries(${PROJECT_NAME} android native_app_glue openxr_loader)
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-cast-calling-convention)







include(../cmake/gfxwrapper.cmake)
if(TARGET openxr-gfxwrapper)
    target_include_directories(
            ${PROJECT_NAME} PUBLIC ${openxr_SOURCE_DIR}/src/common
    )
    target_link_libraries(${PROJECT_NAME} openxr-gfxwrapper)
    target_compile_definitions(
            ${PROJECT_NAME} PUBLIC XR_TUTORIAL_USE_OPENGL_ES
    )
endif()
