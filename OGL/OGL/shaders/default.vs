#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

//out vec3 ourColor;
out vec3 out_pos;

uniform float x_offset;

void main()
{
    gl_Position = vec4(position.x + x_offset, position.y, position.z, 1.0f);
    //ourColor = color;
	out_pos = position;
}