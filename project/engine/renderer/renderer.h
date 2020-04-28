#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"

class				engine::renderer
{
public :
					renderer() = default;
	virtual			~renderer() = default;

	virtual void	render() = 0;

protected :

	template		<engine::memory_management management>
	void			draw(model<management> &model)
	{
		model.use(true);
		//glDrawElements(GL_TRIANGLES, model.eab.size(), GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, model.vbos.vertices.size());
		model.use(false);
	}
};


