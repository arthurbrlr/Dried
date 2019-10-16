#version 330 core

layout (location = 0) in vec2 position;

out vec2 texCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 0.0, 1.0);
    texCoord = vec2( (position.x + 1.0) / 2.0, (position.y + 1.0) / 2.0);
}
