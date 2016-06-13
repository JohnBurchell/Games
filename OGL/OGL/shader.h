#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h> // Include all the OpenGL headers

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
class Shader
{
public:
	//ID of the program
	GLuint Program;
	Shader(const GLchar* vertex_source_path, const GLchar* fragment_shader_source_path);
	void use();
};

#endif //SHADER_H_
