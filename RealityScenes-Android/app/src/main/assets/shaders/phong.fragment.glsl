#version 310 es

// this is a requirement unique to OpenGL ES
precision mediump float;

in vec3 vertexColor;

out vec4 color;

void main() {
    color = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);
}

