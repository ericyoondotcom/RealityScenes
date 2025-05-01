#version 310 es

layout(std140, binding = 0) uniform CameraConstants {
    mat4 viewProj;
    mat4 modelViewProj;
    mat4 model;
};

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec3 vertexPosition;
out vec3 vertexNormal;

void main() {
    vertexNormal = mat3(transpose(inverse(model))) * normal;
    vec4 finalPosition = modelViewProj * vec4(position, 1.0f);
    gl_Position = finalPosition;
    vertexPosition = vec3(model * vec4(position, 1.0f));
}
