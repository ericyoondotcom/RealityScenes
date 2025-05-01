#ifndef REAITYSCENES_EY_SCENE_H
#define REAITYSCENES_EY_SCENE_H

#include <GraphicsAPI_OpenGL_ES.h>
#include <OpenXRDebugUtils.h>
#include <xr_linear_algebra.h>
#include "ey_shared.h"

class EYScene {

};

class EYShader {
public:
    std::string vertexShaderFilepath;
    std::string fragmentShaderFilepath;
    void* vertexShader;
    void* fragmentShader;
    void* pipeline;
    GraphicsAPI* graphicsApi;

    EYShader(GraphicsAPI* graphicsApi, std::string vertexShaderFilepath, std::string fragmentShaderFilepath);
    ~EYShader();

    void CreateShaders(android_app* androidApp);
    void CreatePipeline(std::vector<SwapchainInfo> colorSwapchainInfos, std::vector<SwapchainInfo> depthSwapchainInfos);
};


#endif //REAITYSCENES_EY_SCENE_H 