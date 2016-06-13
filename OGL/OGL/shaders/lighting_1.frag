#version 330 core
out vec4 color;	

in vec3 Normal;
in vec3 Fragment_Position;

uniform vec3 light_position;
uniform vec3 light_colour;
uniform vec3 object_colour;
uniform vec3 view_position;

void main()
{
	// Ambient
	float ambient_strength = 0.1f;
	vec3 ambient = ambient_strength * light_colour;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 light_direction = normalize(light_position - Fragment_Position);
	float difference = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = difference * light_colour;

	// Specular Strength
	float specular_strength = 0.5f;

	vec3 view_direction = normalize(view_position - Fragment_Position);
	vec3 reflect_direction = reflect(-light_direction, norm);

	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
	vec3 specular = specular_strength * spec * light_colour;

	vec3 result = (ambient + diffuse + specular) * object_colour;
    color = vec4(result, 1.0f);
}