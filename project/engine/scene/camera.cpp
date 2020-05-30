#include "camera.h"
#include "engine/core/core.h"

using namespace		engine;

void				scene::camera::move(enum movement movement)
{
	auto 			movement_speed = settings().camera_movement_speed;

	switch (movement)
	{
		case movement::left :
			position -= right * movement_speed;
			break ;

		case movement::right :
			position += right * movement_speed;
			break ;

		case movement::forth :
			position += front * movement_speed;
			break ;

		case movement::back :
			position -= front * movement_speed;
			break ;

		case movement::up :
			position += up * movement_speed;
			break ;

		case movement::down :
			position -= up * movement_speed;
			break ;
	}
}

void				scene::camera::rotate(enum rotation rotation)
{
	auto 			rotation_speed = settings().camera_rotation_speed;

	switch (rotation)
	{
		case rotation::left :
			yaw -= rotation_speed;
			break ;

		case rotation::right :
			yaw += rotation_speed;
			break ;

		case rotation::up :
			pitch += rotation_speed;
			break ;

		case rotation::down :
			pitch -= rotation_speed;
			break ;
	}

	pitch = std::clamp(pitch, -90.f, 90.f);
	update();
}

mat4				scene::camera::projection_matrix() const
{
	return (glm::perspective(
		glm::radians(30.f),
		(float)settings().window_size.x / (float)settings().window_size.y,
		settings().camera_near_plane, settings().camera_far_plane));
}

mat4				scene::camera::view_matrix() const
{
	return (lookAt(position, position + front, up));
}

void				scene::camera::update()
{
	vec3			local_front;

	local_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	local_front.y = sin(glm::radians(pitch));
	local_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = normalize(local_front);
	right = normalize(cross(front, up_const));
	up = normalize(cross(right, front));
}
