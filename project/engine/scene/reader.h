#pragma once

#include "engine/namespace.h"

#include "engine/scene/scene.h"

class					engine::scene::reader
{
public :
						reader() = default;
	virtual				~reader() = default;

protected :

//						Scene
	[[nodiscard]]
	const inline auto	&objects(const shared<engine::scene::scene> &scene) const
	{
		return (scene->objects);
	}

	[[nodiscard]]
	const inline auto	&lights(const shared<engine::scene::scene> &scene) const
	{
		return (scene->lights);
	}

	[[nodiscard]]
	inline bool			lights_have_changed(const shared<engine::scene::scene> &scene) const
	{
		return (scene->lights_have_changed);
	}

	[[nodiscard]]
	inline bool			objects_have_changed(const shared<engine::scene::scene> &scene) const
	{
		return (scene->objects_have_changed);
	}

	inline void			reset_changes(const shared<engine::scene::scene> &scene) const
	{
		scene->lights_have_changed = false;
		scene->objects_have_changed = false;
	}

//						Camera
	inline auto			&camera(const shared<engine::scene::scene> &scene) const
	{
		return (scene->camera);
	}

	[[nodiscard]]
	inline vec3			position(const shared<engine::scene::camera> &camera) const
	{
		return (camera->position);
	}

	[[nodiscard]]
	inline mat4			projection_matrix(const shared<engine::scene::camera> &camera) const
	{
		return (camera->projection_matrix());
	}
	[[nodiscard]]
	inline mat4			view_matrix(const shared<engine::scene::camera> &camera) const
	{
		return (camera->view_matrix());
	}

//						Light
	[[nodiscard]]
	inline auto			type(const shared<engine::scene::light> &light) const
	{
		return (light->type);
	}

	[[nodiscard]]
	inline auto			parameter_a(const shared<engine::scene::light> &light) const
	{
	return (light->parameter_a);
	}

	[[nodiscard]]
	inline auto			parameter_b(const shared<engine::scene::light> &light) const
	{
	return (light->parameter_b);
	}

	[[nodiscard]]
	inline auto			parameter_c(const shared<engine::scene::light> &light) const
	{
	return (light->parameter_c);
	}

	[[nodiscard]]
	inline auto			parameter_d(const shared<engine::scene::light> &light) const
	{
	return (light->parameter_d);
	}

	[[nodiscard]]
	inline auto			color(const shared<engine::scene::light> &light) const
	{
		return (light->color);
	}

	[[nodiscard]]
	inline auto			power(const shared<engine::scene::light> &light) const
	{
		return (light->power);
	}
};