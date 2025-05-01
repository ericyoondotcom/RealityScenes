#ifndef REAITYSCENES_EY_SCENE_H
#define REAITYSCENES_EY_SCENE_H

#include <GraphicsAPI_OpenGL_ES.h>
#include <OpenXRDebugUtils.h>
#include <xr_linear_algebra.h>
#include "ey_shared.h"

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

class EYMesh {
public:
    EYShader* shader;
    GraphicsAPI* graphicsApi;
    void* vertexBuffer;
    void* indexBuffer;
    void* cameraUniformBuffer;
    uint numTriangles;
    XrPosef pose;
    XrVector3f scale;
    CameraConstants cameraConstants;



    EYMesh(
            GraphicsAPI* graphicsApi,
            EYShader *shader,
            float *vertices,
            uint numVertices,
            uint32_t *indices,
            uint numTriangles,
            float *normals,
            XrPosef pose,
            XrVector3f scale
        );
    ~EYMesh();
    void SetPose(XrPosef pose);
    void Render(XrMatrix4x4f viewProj);
};

class EYScene {
public:
    std::vector<EYMesh*> meshes;
    EYScene(std::vector<EYMesh*> meshes);
    ~EYScene();
};



#endif //REAITYSCENES_EY_SCENE_H