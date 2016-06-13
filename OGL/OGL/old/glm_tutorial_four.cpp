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
#include "camera.h"

namespace tutorial_4
{


	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint EBOs[2];
	GLuint texture;
	GLuint texture_two;
	GLfloat mix_variable;

	Camera camera{ glm::vec3{0.0f, 0.0f, 3.0f} };

	unsigned frame_count = 0;

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	GLfloat delta_time = 0.0f;
	GLfloat last_frame = 0.0f;

	GLfloat last_x = WIDTH / 2.0f;
	GLfloat last_y = HEIGHT / 2.0f;

	bool first_mouse = true;
	bool keys[1024];

	void timer_function();
	void idle_function();

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	void texture_triangle()
	{
		GLfloat texCoords[] = {
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};



		glGenVertexArrays(1, VAOs);
		glGenBuffers(1, VBOs);

		glBindVertexArray(VAOs[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


		//Point to the correct postions in the VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Texture attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
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

	void do_movement()
	{
		if (keys[GLFW_KEY_W])
		{
			camera.process_keyboard(Camera_Movement::Forward, delta_time);
		}
		if (keys[GLFW_KEY_S])
		{
			camera.process_keyboard(Camera_Movement::Backward, delta_time);
		}
		if (keys[GLFW_KEY_A])
		{
			camera.process_keyboard(Camera_Movement::Left, delta_time);
		}
		if (keys[GLFW_KEY_D])
		{
			camera.process_keyboard(Camera_Movement::Right, delta_time);
		}
	}

	//Callback for handling key presses.
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{

		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}

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

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
	
		if (first_mouse)
		{
			last_x = xpos;
			last_y = ypos;
			first_mouse = false;
		}

		GLfloat x_offset = xpos - last_x;
		GLfloat y_offset = last_y - ypos;

		last_x = xpos;
		last_y = ypos;
	
		camera.process_mouse_movement(x_offset, y_offset);
	}

	void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
	{
		camera.process_mouse_scroll(glm::radians(y_offset));
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
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

		Shader shader("shaders/viewing.vs", "shaders/viewing.frag");
		//Tutorial Three
		texture_triangle();

		//Simple loop
		while (!glfwWindowShouldClose(window))
		{
			GLfloat current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			last_frame = current_frame;

			glfwPollEvents();
			do_movement();

			//Set clear colour to ensure that we're actually rendering something
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

			shader.use();

			// Create transformations
			glm::mat4 model;
			glm::mat4 projection;
			//model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 view;
			view = camera.get_view_matrix();
			projection = glm::perspective(camera.m_zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

			// Get their uniform location
			GLint modelLoc = glGetUniformLocation(shader.Program, "model");
			GLint viewLoc = glGetUniformLocation(shader.Program, "view");
			GLint projLoc = glGetUniformLocation(shader.Program, "projection");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			//Drawing
			glBindVertexArray(VAOs[0]);
			glEnable(GL_DEPTH_TEST);

			for (GLuint i = 0; i < 10; ++i)
			{
				glm::mat4 model;
				model = glm::translate(model, cubePositions[i]);

				GLfloat angle = glm::radians(20.0f * i);

				if (i % 3 == 0)
				{
					angle = glm::radians(50.0f) * (GLfloat)glfwGetTime();
				}

				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		//Cleanup
		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);

		glfwTerminate();
		return 0;
	}
}
