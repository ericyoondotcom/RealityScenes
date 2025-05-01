#version 310 es

uniform CameraConstants {
    mat4 viewProj;
    mat4 modelViewProj;
    mat4 model;
};

layout(location=0) in vec3 position;
layout(location=1) in vec3 normals;

out vec3 vertexColors;

void main() {
    // gl_Position = modelViewProj * position;
    gl_Position = position + vec3(0.0f, 0.0f, 3.0f);
    vertexColors = vec3(1.0f, 0.0f, 1.0f);rrdfsdfsdafs
}
