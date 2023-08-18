#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

out vec4 FragPos;
out vec4 ShadowCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    FragPos = model * vec4(inPosition, 1.0);
    gl_Position = projection * view * FragPos;
    ShadowCoord = lightSpaceMatrix * FragPos;
}
