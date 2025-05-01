#version 310 es

uniform CameraConstants {
    mat4 viewProj;
    mat4 modelViewProj;
    mat4 model;
};

layout(location=0) in vec3 position;
layout(location=1) in vec3 normals;

out vec3 vertexColor;

void main() {
    gl_Position = modelViewProj * vec4(position, 1.0f);
    vertexColor = normals;
}
