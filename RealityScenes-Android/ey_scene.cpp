#include "ey_scene.h"

#include <utility>

EYShader::EYShader(GraphicsAPI* graphicsApi, std::string vertexShaderFilepath, std::string fragmentShaderFilepath) {
    this->graphicsApi = graphicsApi;
    this->vertexShaderFilepath = std::move(vertexShaderFilepath);
    this->fragmentShaderFilepath = std::move(fragmentShaderFilepath);
}

void EYShader::CreateShaders(android_app* androidApp) {
    std::string vertexSource = ReadTextFile("shaders/VertexShader_GLES.glsl", androidApp->activity->assetManager);
    vertexShader = graphicsApi->CreateShader({GraphicsAPI::ShaderCreateInfo::Type::VERTEX, vertexSource.data(), vertexSource.size()});
    std::string fragmentSource = ReadTextFile("shaders/PixelShader_GLES.glsl", androidApp->activity->assetManager);
    fragmentShader = graphicsApi->CreateShader({GraphicsAPI::ShaderCreateInfo::Type::FRAGMENT, fragmentSource.data(), fragmentSource.size()});
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
