#ifndef CAMERA_H_
#define CAMERA_H_
#pragma once

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace
{
	enum class Camera_Movement
	{
		Forward,
		Backward,
		Left,
		Right
	};

	constexpr GLfloat YAW         = -90.0f;
	constexpr GLfloat PITCH		  =	 0.0f;
	constexpr GLfloat SPEED       =  3.0f;
	constexpr GLfloat SENSITIVITY =  0.25f;
	constexpr GLfloat ZOOM        =  45.0f;
}

class Camera
{
public:

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

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: m_movement_speed{ SPEED }, m_mouse_sensitivity{ SENSITIVITY }, m_zoom{ ZOOM }, m_position{ position }, m_front{ glm::vec3{0.0f, 0.0f, -1.0f} },
		m_world_up{ up }, m_yaw{ yaw }, m_pitch{ pitch }
	{
		update_camera_vectors();
	}
	Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat up_x, GLfloat up_y, GLfloat up_z, GLfloat yaw, GLfloat pitch)
		: m_movement_speed{ SPEED }, m_mouse_sensitivity { SENSITIVITY }, m_zoom { ZOOM }, m_front{ glm::vec3{ 0.0f, 0.0f, -1.0f } },
		m_position{ glm::vec3{pos_x, pos_y, pos_z} }, m_world_up{ glm::vec3{up_x, up_y, up_z} }, m_yaw{ yaw }, m_pitch{ pitch }
	{
		update_camera_vectors();
	}

	//Return the view matrix calculated using Euler angles and the lookat matrix
	glm::mat4 get_view_matrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	//Process input received from any keyboard-like input system. Accepts input parameter in the form of camera defined enum (to abstract it from windowing systems)
	void process_keyboard(Camera_Movement direction, GLfloat delta)
	{
		GLfloat velocity = m_movement_speed * delta;
		if (direction == Camera_Movement::Forward)
		{
			m_position += m_front * velocity;
		}
		if (direction == Camera_Movement::Backward)
		{
			m_position -= m_front * velocity;
		}
		if (direction == Camera_Movement::Left)
		{
			m_position -= m_right * velocity;
		}
		if (direction == Camera_Movement::Right)
		{
			m_position += m_right * velocity;
		}
	}

	//Process input received from a mouse input systems. Expects the offset value in both the x and y direction.
	void process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true)
	{
		x_offset *= m_mouse_sensitivity;
		y_offset *= m_mouse_sensitivity;

		m_yaw   += x_offset;
		m_pitch += y_offset;

		//Ensure that if the pitch is out of bounds, the screen does not flip.
		if (constrain_pitch)
		{
			if (m_pitch > 89.0f)
			{
				m_pitch = 89.0f;
			}
			if (m_pitch < -89.0f)
			{
				m_pitch = -89.0f;
			}
		}

		update_camera_vectors();
	}

	//Process input received from a mouse scroll-wheel event. Only requires input on the verticle wheel-axis
	void process_mouse_scroll(GLfloat y_offset)
	{
		if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		{
			m_zoom -= y_offset;
		}
		if (m_zoom <= 1.0f)
		{
			m_zoom = 1.0f;
		}
		if (m_zoom >= 45.0f)
		{
			m_zoom = 45.0f;
		}
	}

private:
	//Calculates the front vector from the Camera's (updated) euler angles
	void update_camera_vectors()
	{
		//Calculate the new front vector
		glm::vec3 front{};
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);
		//Also re-calculate the right and up vector
		m_right = glm::normalize(glm::cross(m_front, m_world_up));
		m_up    = glm::normalize(glm::cross(m_right, m_front));
	}
};


#endif //CAMERA_H_
