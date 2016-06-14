#include "camera.h"

void Camera::process_keyboard(Camera_Movement direction, GLfloat delta)
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

void Camera::process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch)
{
	x_offset *= m_mouse_sensitivity;
	y_offset *= m_mouse_sensitivity;

	m_yaw += x_offset;
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

void Camera::process_mouse_scroll(GLfloat y_offset)
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

void Camera::update_camera_vectors()
{
	//Calculate the new front vector
	glm::vec3 front{};
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	//Also re-calculate the right and up vector
	m_right = glm::normalize(glm::cross(m_front, m_world_up));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}