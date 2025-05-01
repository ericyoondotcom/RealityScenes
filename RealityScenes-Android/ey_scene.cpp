#include "ey_scene.h"
#include "DebugOutput.h"

#include <utility>

EYShader::EYShader(GraphicsAPI* graphicsApi, std::string vertexShaderFilepath, std::string fragmentShaderFilepath) {
    this->graphicsApi = graphicsApi;
    this->vertexShaderFilepath = std::move(vertexShaderFilepath);
    this->fragmentShaderFilepath = std::move(fragmentShaderFilepath);
}

void EYShader::CreateShaders(android_app* androidApp) {
    XR_TUT_LOG(vertexShaderFilepath);
    XR_TUT_LOG(fragmentShaderFilepath);
    std::string vertexSource = ReadTextFile(vertexShaderFilepath, androidApp->activity->assetManager);
    vertexShader = graphicsApi->CreateShader({GraphicsAPI::ShaderCreateInfo::Type::VERTEX, vertexSource.data(), vertexSource.size()});
    std::string fragmentSource = ReadTextFile(fragmentShaderFilepath, androidApp->activity->assetManager);
    fragmentShader = graphicsApi->CreateShader({GraphicsAPI::ShaderCreateInfo::Type::FRAGMENT, fragmentSource.data(), fragmentSource.size()});

    // log whether the vertex sahder is null
    XR_TUT_LOG(vertexSource.data());
    XR_TUT_LOG(fragmentSource.data());
    XR_TUT_LOG("Vertex shader: " + std::to_string(vertexShader == nullptr));
    XR_TUT_LOG("Fragment shader: " + std::to_string(fragmentShader == nullptr));
}

void EYShader::CreatePipeline(std::vector<SwapchainInfo> colorSwapchainInfos, std::vector<SwapchainInfo> depthSwapchainInfos) {
    GraphicsAPI::PipelineCreateInfo pipelineCI;
    pipelineCI.shaders = {vertexShader, fragmentShader};
    pipelineCI.vertexInputState.attributes = {{0, 0, GraphicsAPI::VertexType::VEC4, 0, "TEXCOORD"}};
    pipelineCI.vertexInputState.bindings = {{0, 0, 4 * sizeof(float)}};
    pipelineCI.inputAssemblyState = {GraphicsAPI::PrimitiveTopology::TRIANGLE_LIST, false};
    pipelineCI.rasterisationState = {false, false, GraphicsAPI::PolygonMode::FILL, GraphicsAPI::CullMode::BACK, GraphicsAPI::FrontFace::COUNTER_CLOCKWISE, false, 0.0f, 0.0f, 0.0f, 1.0f};
    pipelineCI.multisampleState = {1, false, 1.0f, 0xFFFFFFFF, false, false};
    pipelineCI.depthStencilState = {true, true, GraphicsAPI::CompareOp::LESS_OR_EQUAL, false, false, {}, {}, 0.0f, 1.0f};
    pipelineCI.colorBlendState = {false, GraphicsAPI::LogicOp::NO_OP, {{true, GraphicsAPI::BlendFactor::SRC_ALPHA, GraphicsAPI::BlendFactor::ONE_MINUS_SRC_ALPHA, GraphicsAPI::BlendOp::ADD, GraphicsAPI::BlendFactor::ONE, GraphicsAPI::BlendFactor::ZERO, GraphicsAPI::BlendOp::ADD, (GraphicsAPI::ColorComponentBit)15}}, {0.0f, 0.0f, 0.0f, 0.0f}};
    pipelineCI.colorFormats = {colorSwapchainInfos[0].swapchainFormat};
    pipelineCI.depthFormat = depthSwapchainInfos[0].swapchainFormat;
    pipelineCI.layout = {{0, nullptr, GraphicsAPI::DescriptorInfo::Type::BUFFER, GraphicsAPI::DescriptorInfo::Stage::VERTEX},
                         {1, nullptr, GraphicsAPI::DescriptorInfo::Type::BUFFER, GraphicsAPI::DescriptorInfo::Stage::VERTEX},
                         {2, nullptr, GraphicsAPI::DescriptorInfo::Type::BUFFER, GraphicsAPI::DescriptorInfo::Stage::FRAGMENT}};
    pipeline = graphicsApi->CreatePipeline(pipelineCI);
}

EYShader::~EYShader() {
    graphicsApi->DestroyPipeline(pipeline);
    graphicsApi->DestroyShader(fragmentShader);
    graphicsApi->DestroyShader(vertexShader);
}

EYMesh::EYMesh(
        GraphicsAPI* graphicsApi,
        EYShader *shader,
        float *vertices,
        uint numVertices,
        uint32_t *indices,
        uint numTriangles,
        float *normals
) {
    this->numTriangles = numTriangles;
    this->graphicsApi = graphicsApi;
    this->shader = shader;

    float* allData = new float[numVertices * 6];
    for(int i = 0; i < numVertices; i++) {
        allData[i * 6 + 0] = vertices[i + 0];
        allData[i * 6 + 1] = vertices[i + 1];
        allData[i * 6 + 2] = vertices[i + 2];
        allData[i * 6 + 3] = normals[i + 0];
        allData[i * 6 + 4] = normals[i + 1];
        allData[i * 6 + 5] = normals[i + 2];
    }

    vertexBuffer = graphicsApi->CreateBuffer({
        GraphicsAPI::BufferCreateInfo::Type::VERTEX,
        sizeof(float) * 4,
        numVertices * 6,
        allData // TODO: do we need "&"?
    });
    indexBuffer = graphicsApi->CreateBuffer({
        GraphicsAPI::BufferCreateInfo::Type::INDEX,
        sizeof(uint32_t),
        numTriangles * 3,
        indices
    });

    delete[] allData;
}

void EYMesh::Render(XrPosef pose, XrVector3f scale, XrVector3f color) {

}

EYMesh::~EYMesh() {
    graphicsApi->DestroyBuffer(indexBuffer);
    graphicsApi->DestroyBuffer(vertexBuffer);
}

EYScene::EYScene(std::vector<EYMesh *> meshes) {
    this->meshes = std::move(meshes);
}

EYScene::~EYScene() {
    // Destroy all meshes in the vector
    for (auto mesh : meshes) {
        delete mesh;
    }
    meshes.clear();
    // Destroy the vector itself
    meshes.~vector();
}
