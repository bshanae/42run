#pragma once

#include "engine/namespace.h"
#include "engine/model/vbo.h"
#include "engine/model/eab.h"
#include "engine/model/vao.h"

template							<engine::memory_management management>
class							engine::model
{
	friend class 				renderer;

public :
								model() = default;
								~model() = default;

	void						use(bool state) const
	{
		vao.use(state);
		indices.use(state);
	}

	void						save()
	{
		vao.use(true);
		vao.connect(vertices);
		vertices.save();
		vao.use(false);

		indices.save();
	}

protected :

	vbo<float, 3, management>	vertices;
	class eab					indices;

private :

	class vao					vao;
};