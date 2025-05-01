#version 310 es

// this is a requirement unique to OpenGL ES
precision mediump float;

in vec3 vertexPosition;
in vec3 vertexNormal;

layout(std140, binding = 1) uniform LightPositionStruct {
    float lpx;
    float lpy;
    float lpz;
};
layout(std140, binding = 2) uniform ViewPositionStruct {
    float vpx;
    float vpy;
    float vpz;
};

out vec4 color;

void main() {
    // Use the uniform values instead of hardcoded ones
    vec3 lightPosition = vec3(1, 1, 0);
    vec3 viewPosition = vec3(0, 0, 0);

    float AMBIENT_STRENGTH = 0.07;
    float DIFFUSE_STRENGTH = 0.5;
    float SPECULAR_STRENGTH = 0.7;
    float SHININESS = 32.0;
    vec3 AMBIENT_COLOR = vec3(1.0, 0.0, 0.0);
    vec3 DIFFUSE_COLOR = vec3(0.0, 0.0, 0.0);
    vec3 SPECULAR_COLOR = vec3(0.0, 0.0, 1.0);

    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(lightPosition - vertexPosition);

    vec3 ambient = AMBIENT_STRENGTH * AMBIENT_COLOR;

    float diffuseFactor = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = DIFFUSE_STRENGTH * diffuseFactor * DIFFUSE_COLOR;

    vec3 viewDir = normalize(viewPosition - vertexPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SHININESS);
    vec3 specular = SPECULAR_STRENGTH * spec * SPECULAR_COLOR;

    color = vec4(ambient + diffuse + specular, 1.0);
}

