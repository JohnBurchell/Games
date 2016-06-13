#version 330 core
//in vec3 ourColor;
in vec3 out_pos;

out vec4 color;

void main()
{
    color = vec4(out_pos, 1.0f);
}