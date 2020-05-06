#pragma once

#include "engine/namespace.h"

class						engine::scene::camera
{
	friend class			engine::renderer;

public :

	static inline float		movement_speed = 0.f;
	static inline float		rotation_speed = 0.f;
	static inline auto		initial_position = vec3(0.f, 0.f, 0.f);
	static inline float		initial_yaw = -90.f;
	static inline float		initial_pitch = 0.f;
	static inline float		near_plane = 0.1f;
	static inline float		far_plane = 100.f;

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
	vec3					position = initial_position;
	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(0.f, 0.f, 0.f);

	float					yaw = initial_yaw;
	float					pitch = initial_pitch;

	void					update();
};
