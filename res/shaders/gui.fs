#version 330 core

out vec4 fragmentColor;

in vec2 texCoord;

uniform sampler2D guiTexture;

void main() {
    fragmentColor = texture(guiTexture, texCoord);
}
