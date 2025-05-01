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
    vec4 TEMP_DELETE_ME = modelViewProj * vec4(position, 1.0f);
    gl_Position = vec4(position.x, position.y, position.z - 3.0f, 1.0f);
    vertexColor = vec3(1.0f, 0.0f, 0.0f);
}
