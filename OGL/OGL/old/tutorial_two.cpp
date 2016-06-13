//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

namespace tut_two
{

	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint EBO;

	void tut_two_shaders()
	{

		/*
		Start of binding process
		*/

		//Array of vertex positions
		GLfloat vertices[] =
		{
			//Positions - x,y,z  - Colours r,g,b
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //Top Right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //Top Left
			-0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  //Top
		};

		glGenBuffers(2, VBOs);
		glGenVertexArrays(2, VAOs);
		glBindVertexArray(VAOs[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Colour attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

	}

	//Callback for handling key presses.
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		//When the user presses the escape key, set WindowShouldClose to true, thus closing the application.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	int mains()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "Learning some OpenGL", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);

		//Check to make sure the window is not null. If it is, terminate.
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		//Initialise GLEW
		//glewExperimental allows us to use modern techniques. Not setting it to true might lead to complications
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialise GLEW" << std::endl;
			return -1;
		}

		//Tell OpenGL the size of the window, or in this case the viewport, that we wish to render to
		glViewport(0, 0, 800, 600);

		Shader shader("shaders/default.vs", "shaders/default.frag");
		//Tutorial Two
		tut_two_shaders();

		//Simple loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			//Set clear colour to ensure that we're actually rendering something
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Drawning
			//Offset by one
			GLfloat x_offset = 0.5f;
			GLint offset_location = glGetUniformLocation(shader.Program, "x_offset");
			shader.use();
			glUniform1f(offset_location, x_offset);

			glBindVertexArray(VAOs[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//Polygon mode aka wireframe mode
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		//Cleanup
		glDeleteVertexArrays(1, VAOs);
		glDeleteBuffers(1, VBOs);

		glfwTerminate();
		return 0;
	}

}// Tut Two

