#version 330 core

///////////////////////////////////////////////////////////////////////////////
//								IN-OUT
///////////////////////////////////////////////////////////////////////////////

#define BONES_IN_VERTEX			6
#define BONES_IN_SKELETON		100

layout(location = 0) in vec3	in_position;
layout(location = 1) in vec3	in_normal;
layout(location = 2) in vec2	in_UV;
layout(location = 3) in float	in_bones_ids[BONES_IN_VERTEX];

//								Weights location is set according to BONES_IN_VERTEX macro
layout(location = 9) in float	in_bones_weights[BONES_IN_VERTEX];

out vec3						pass_position;
out vec3						pass_normal;
out vec2						pass_UV;

///////////////////////////////////////////////////////////////////////////////
//								UNIFORM
///////////////////////////////////////////////////////////////////////////////

uniform mat4					uniform_projection;
uniform mat4					uniform_view;

uniform mat4					uniform_local;
uniform mat4					uniform_model;

uniform bool					uniform_does_mesh_have_bones;
uniform mat4					uniform_bones_transformations[BONES_IN_SKELETON];

void							main()
{
	mat4						bones_transformation = mat4(1.0);

	if (uniform_does_mesh_have_bones)
	{
		bones_transformation = mat4(0.0);

		for (int i = 0; i < BONES_IN_VERTEX; i++)
			bones_transformation += uniform_bones_transformations[int(in_bones_ids[i])] * in_bones_weights[i];
	}

	pass_position = in_position;
	pass_normal = in_normal;
	pass_UV = in_UV;

	gl_Position = uniform_projection * uniform_view * bones_transformation * vec4(in_position, 1.f);
}