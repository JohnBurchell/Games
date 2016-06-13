#version 330 core
in vec3 our_colour;
in vec2 tex_coord;

out vec4 colour;

uniform sampler2D texture_one;
uniform sampler2D texture_two;
uniform float mix_variable;

void main()
{
	//Flip the image back around
	colour = mix(texture(texture_one, tex_coord), texture(texture_two, vec2(-tex_coord.x, -tex_coord.y)), mix_variable);
}