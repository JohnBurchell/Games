#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 Tex_Coord;

out vec3 our_colour;
out vec2 tex_coord;

void main()
{
	gl_Position = vec4(position, 1.0f);
	our_colour = colour;
	tex_coord = Tex_Coord;
}