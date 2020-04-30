#pragma once

#include "engine/namespace.h"

#include "engine/old_model/model.h"

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
		glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, nullptr);
		model.use(false);
	}
};


