#version 330 core
in vec2 tex_coords;

out vec4 colour;

uniform sampler2D screen_texture;

void main()
{
	colour = texture(screen_texture, tex_coords);
}

