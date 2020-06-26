#pragma once

#include "engine/namespace.h"

class						engine::scene::camera
{
	friend class			engine::scene::reader;

public :
							camera()
	{
		update();
	}
							~camera() = default;

	enum class 				movement
	{
		forth,
		back,
		left,
		right,
		up,
		down
	};

	void					move(enum movement movement);

	enum class				rotation
	{
		left,
		right,
		up,
		down
	};

	void					rotate(enum rotation rotation);

	[[nodiscard]]
	mat4					projection_matrix() const;
	[[nodiscard]]
	mat4					view_matrix() const;

private :

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					position = settings().camera_position;

	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(0.f, 0.f, 0.f);

	float					yaw = settings().camera_yaw;
	float					pitch = settings().camera_pitch;

	void					update();
};
