#pragma once

#include "engine/namespace.h"
#include "engine/model/vbo.h"
#include "engine/model/eab.h"
#include "engine/model/vao.h"

template							<engine::memory_management management>
class								engine::model
{
	friend class 					renderer;

public :
									model() = default;
									~model() = default;

	void							use(bool state) const
	{
		vao.use(state);
	}

	void							save()
	{
		vao.use(true);
		vao.connect(vbos.vertices);
		vbos.vertices.save();
		vao.use(false);
	}

protected :

	struct
	{
		vbo<float, 3, management>	vertices;
	}								vbos;
	class eab						eab;
	class vao						vao;
};