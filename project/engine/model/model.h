#pragma once

#include "engine/namespace.h"

#include "engine/model/flag.h"
#include "engine/model/material.h"
#include "engine/model/mesh.h"
#include "engine/model/skeleton.h"
#include "engine/model/animation.h"

class							engine::model::model
{
	friend class				engine::core;
	friend class				engine::model::loader;
	friend class				engine::model::reader;

public :
								model() = default;
								model(const path &source, flag_wrapper flags);

								~model() = default;

//	---------------------------	Building at runtime

	void						push(unique<mesh> &mesh);

	template					<typename ...args_type>
	void						emplace(args_type &&...args)
	{
		auto					mesh = make_unique<engine::model::mesh>(args...);

		meshes.push_back(move(mesh));
	}

//	---------------------------	Animation

	void						animate(const animation &animation)
	{
		skeleton->animate(animation);
	}

	[[nodiscard]] bool			is_animation_playing() const
	{
		return (skeleton->animation != nullopt);
	}

	[[nodiscard]] float			current_animation_timestamp() const
	{
		return (skeleton->time);
	}

//	---------------------------	Analysis

	[[nodiscard]] vec3			min() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analysis.min);
	}

	[[nodiscard]] vec3			max() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analysis.max);
	}

	[[nodiscard]] vec3			size() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analysis.size);
	}

	[[nodiscard]] vec3			offset() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analysis.offset);
	}

private :

	static inline
	shared<loader>				loader;

//								Used when model is loaded from file
	shared_ptr<const aiScene>	assimp_scene;

//								Locked when loaded from file
	bool						is_locked = false;

	void						analyze();
	void						center();

	vector<unique<mesh>>		meshes;
	unique<skeleton>			skeleton;

	bool						is_analyzed = false;
	bool						is_centered = false;

public :

	struct						analysis
	{
		vec3					min;
		vec3					max;
		vec3					size;
		vec3					offset;
	};

private :

	analysis					analysis;
};

