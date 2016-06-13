#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture_one;
uniform sampler2D texture_two;
uniform float mix_variable;

void main()
{
    color = mix(texture(texture_one, TexCoord), texture(texture_two, TexCoord), mix_variable);
}