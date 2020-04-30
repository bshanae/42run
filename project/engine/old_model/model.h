#pragma once

#include "engine/namespace.h"
#include "engine/old_model/vbo.h"
#include "engine/old_model/eab.h"
#include "engine/old_model/vao.h"

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

		if (not is_connected)
		{
			vao.connect(vertices);
			vao.connect(colors);
		}

		vertices.save();
		colors.save();

		vao.use(false);

		indices.save();
		is_connected = true;
	}

protected :

	vbo<float, 3, management>	vertices;
	vbo<float, 4, management>	colors;
	class eab					indices;

private :

	bool						is_connected = false;

	class vao					vao;
};