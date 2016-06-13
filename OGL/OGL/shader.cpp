#include "shader.h"

#include <GL/glew.h> // Include all the OpenGL headers
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using std::string;
using std::ifstream;
using ss = std::stringstream;
using std::cout;
using std::endl;

Shader::Shader(const GLchar* vertex_source_path, const GLchar* fragment_shader_source_path)
{
	//Get the shader from the filepath
	string vertex_code;
	string fragment_code;
	try
	{
		ifstream v_shader_file{ vertex_source_path };
		ifstream f_shader_file{fragment_shader_source_path};
		ss v_shader_stream, f_shader_stream;
		//Read contents into streams
		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();
		//Close file handlers
		v_shader_file.close();
		f_shader_file.close();
		//Convert stream into GLchar array
		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();
	}
	//Maybe remove this if I use it later and decide not to use exceptions
	catch (std::exception e)
	{
		cout << "ERROR::SHADER::FILE_NOT_READ_SUCCESSFULLY" << endl;
	}

	//Feels like this should be broken out of this, it's getting a bit mixed! - Refactor this later
	GLuint vertex, fragment;
	GLint success;
	GLchar info_log[512];

	const GLchar* p_vertex_shader_code = vertex_code.c_str();
	const GLchar* p_fragment_shader_code = fragment_code.c_str();

	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &p_vertex_shader_code, nullptr);
	glCompileShader(vertex);
	//Check for errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, info_log);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &p_fragment_shader_code, nullptr);
	glCompileShader(fragment);
	//Check for errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, info_log);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	
	//Notify of linking errors, if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, nullptr, info_log);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << endl;
	}

	//Cleanup shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(this->Program);
}


