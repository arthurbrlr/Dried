#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec4 aColor;

out vec4 vertexColor;
out vec2 texCoord;
out vec3 surfaceNormal;
out vec3 toLightVector; // unused

uniform mat4 transform;
uniform mat4 cameraView;
uniform mat4 projection;
uniform vec3 mainLightPosition;

void main() {
    vec4 vWorldPosition = transform * vec4(aPos, 1.0);
    gl_Position = projection * cameraView * vWorldPosition;

    texCoord = aTexCoord;
    
    vertexColor = aColor; // gl_Position + vec4(0.5, 0.5, 0.5, 0.0);

    surfaceNormal = (transform * vec4(aNormal, 1.0)).xyz;
    toLightVector = mainLightPosition - vWorldPosition.xyz; // unused
}
