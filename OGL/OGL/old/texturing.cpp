//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"

namespace texturing {


	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture;
	GLuint texture_two;
	GLfloat mix_variable;

	void texture_triangle()
	{
		GLfloat texCoords[] =
		{
			//Positions		      // Colour           // Texture Coords
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, // Top Right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, // Bottom Right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f  // Top Left 
		};

		GLuint indices[] =
		{
			0, 1, 3, //Triangle one
			1, 2, 3  //Triangle two
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Point to the correct postions in the VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		//Create texture GLuint, tell OGL how many textures we want to make
		glGenTextures(1, &texture);

		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//set texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Load a texture using SOIL
		int width, height;
		unsigned char* image = SOIL_load_image("media/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

		//Generate the Texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind and free up soil data
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Create texture GLuint, tell OGL how many textures we want to make
		glGenTextures(1, &texture_two);

		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, texture_two);

		//set texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Load a texture using SOIL
		int width_two, height_two;
		unsigned char* image_two = SOIL_load_image("media/awesomeface.png", &width_two, &height_two, 0, SOIL_LOAD_RGB);

		//Generate the Texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_two, height_two, 0, GL_RGB, GL_UNSIGNED_BYTE, image_two);
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind and free up soil data
		SOIL_free_image_data(image_two);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//Callback for handling key presses.
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		//When the user presses the escape key, set WindowShouldClose to true, thus closing the application.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key == GLFW_KEY_UP)
		{
			//Increase smiley face transparency
			mix_variable += 0.01f;
		}
		else if (key == GLFW_KEY_DOWN)
		{
			//Decrease simley face transparency and increase box?
			mix_variable -= 0.01f;
		}
	}

	int main()
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

		Shader shader("shaders/texture_shader.vs", "shaders/texture_shader.frag");
		//Tutorial Three
		texture_triangle();

		//Simple loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			//Set clear colour to ensure that we're actually rendering something
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Bind the texture
			glBindTexture(GL_TEXTURE_2D, texture);
			glBindTexture(GL_TEXTURE_2D, texture_two);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(shader.Program, "texture_one"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_two);
			glUniform1i(glGetUniformLocation(shader.Program, "texture_two"), 1);
			//Get location
			GLuint location = glGetUniformLocation(shader.Program, "mix_variable");
			glUniform1f(location, mix_variable);

			//Drawning
			shader.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		//Cleanup
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		glfwTerminate();
		return 0;
	}

}//Namespace

