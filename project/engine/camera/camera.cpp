#include "camera.h"
#include "engine/core/core.h"

using namespace		engine;

void				camera::move(enum movement movement)
{
//	if (axis == axis::x)
//		position += right * movement_speed * (float)sign;
//	else if (axis == axis::y)
//		position += up * movement_speed * (float)sign;
//	else if (axis == axis::z)
//		position += front * movement_speed * -1.f * (float)sign;
}

void				camera::rotate(enum rotation rotation)
{
//	auto			add_if_safe = [](float *target, float value, float range)
//	{
//		const float	temp = *target + value;
//
//		if (temp > -1 * range and temp < range)
//			*target = temp;
//	};
//
//	if (axis == axis::x)
//		add_if_safe(&pitch, (float)sign * rotation_speed, 90.f);
//	else if (axis == axis::y)
//		yaw += -1.f * (float)sign * rotation_speed;
//	update();
}

mat4				camera::projection_matrix() const
{
	return (glm::perspective(
		glm::radians(30.f),
		(float)core::window_size.x / (float)core::window_size.y,
		near_plane, far_plane));
}

mat4				camera::view_matrix() const
{
	return (lookAt(position, position + front, up));
}

void				camera::update()
{
	vec3			local_front;

	local_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	local_front.y = sin(glm::radians(pitch));
	local_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = normalize(local_front);
	right = normalize(cross(front, up_const));
	up = normalize(cross(right, front));
}
