#version 330 core

out vec4 fragmentColor;

in vec4 vertexColor;
in vec2 texCoord;
in vec3 surfaceNormal;
in vec3 toLightVector; // unused

uniform sampler2D texture_atlas;
uniform vec3 mainLightColor;

void main() {

    //vec3 unitToLight = normalize(toLightVector);
    //vec3 unitNormal = normalize(surfaceNormal);
    //float nDotP = dot(unitToLight, unitNormal);
    float brightness;

    if (surfaceNormal.y == -1) brightness = 0.5;
    else if (surfaceNormal.y == 1) brightness = 1.0;
    else brightness = 0.75;

    vec3 diffuse = brightness * mainLightColor;

    fragmentColor = vec4(diffuse, 1.0) * texture(texture_atlas, texCoord);
}
