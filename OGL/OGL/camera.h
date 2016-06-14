#ifndef CAMERA_H_
#define CAMERA_H_
#pragma once

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace
{
	constexpr GLfloat YAW         = -90.0f;
	constexpr GLfloat PITCH		  =	 0.0f;
	constexpr GLfloat SPEED       =  5.0f;
	constexpr GLfloat SENSITIVITY =  0.25f;
	constexpr GLfloat ZOOM        =  45.0f;
}

class Camera
{
public:

	enum class Camera_Movement
	{
		Forward,
		Backward,
		Left,
		Right
	};

	//Camera Options
	GLfloat m_movement_speed;
	GLfloat m_mouse_sensitivity;
	GLfloat m_zoom;
	//Camera Attributues
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_world_up;
	//Euler angles
	GLfloat m_yaw;
	GLfloat m_pitch;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : 
		m_movement_speed{ SPEED }, 
		m_mouse_sensitivity{ SENSITIVITY }, 
		m_zoom{ ZOOM }, m_position{ position }, 
		m_front{ glm::vec3{0.0f, 0.0f, -1.0f} },
		m_world_up{ up }, 
		m_yaw{ yaw }, 
		m_pitch{ pitch }
	{
		update_camera_vectors();
	}
	Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat up_x, GLfloat up_y, GLfloat up_z, GLfloat yaw, GLfloat pitch)
		: 
		m_movement_speed{ SPEED }, 
		m_mouse_sensitivity { SENSITIVITY }, 
		m_zoom { ZOOM }, 
		m_front{ glm::vec3{ 0.0f, 0.0f, -1.0f } },
		m_position{ glm::vec3{pos_x, pos_y, pos_z} }, 
		m_world_up{ glm::vec3{up_x, up_y, up_z} }, 
		m_yaw{ yaw }, 
		m_pitch{ pitch }
	{
		update_camera_vectors();
	}

	//Return the view matrix calculated using Euler angles and the lookat matrix
	glm::mat4 get_view_matrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void process_keyboard(Camera_Movement direction, GLfloat delta);
	void process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true);
	void process_mouse_scroll(GLfloat y_offset);

private:
	//Calculates the front vector from the Camera's updated euler angles
	void update_camera_vectors();
};


#endif //CAMERA_H_
