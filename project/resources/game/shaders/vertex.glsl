///////////////////////////////////////////////////////////////////////////////
//								IN-OUT
///////////////////////////////////////////////////////////////////////////////

layout(location = 0) in vec3	in_position;
layout(location = 1) in vec3	in_normal;
layout(location = 2) in vec2	in_UV;
layout(location = 3) in float	in_bones_ids[SHARED_BONES_IN_VERTEX];

//								Weights location is set according to SHARED_BONES_IN_VERTEX macro
layout(location = 9) in float	in_bones_weights[SHARED_BONES_IN_VERTEX];

out vec3						pass_position;
out vec3						pass_normal;
out vec2						pass_UV;
out float						pass_distance_to_camera;

///////////////////////////////////////////////////////////////////////////////
//								UNIFORM
///////////////////////////////////////////////////////////////////////////////

uniform mat4					uniform_projection;
uniform mat4					uniform_view;

uniform bool					uniform_does_mesh_have_bones;
uniform mat4					uniform_bones_transformations[SHARED_BONES_IN_SKELETON];

uniform struct
{
	mat4						scaling;
	mat4						translation;
	mat4						rotation;
}								uniform_instance;

uniform struct
{
	mat4						scaling;
	mat4						translation;
	mat4						rotation;
}								uniform_group;

///////////////////////////////////////////////////////////////////////////////
//								MAIN
///////////////////////////////////////////////////////////////////////////////

void							main()
{
	mat4						bones_transformation = mat4(1.0);

	mat4						instance_transformation;
	mat4						group_transformation;

	vec4						position;

	if (uniform_does_mesh_have_bones)
	{
		bones_transformation = mat4(0.0);

		for (int i = 0; i < SHARED_BONES_IN_VERTEX; i++)
			bones_transformation += uniform_bones_transformations[int(in_bones_ids[i])] * in_bones_weights[i];
	}

	instance_transformation = uniform_instance.translation * uniform_instance.rotation * uniform_instance.scaling;
	group_transformation = uniform_group.translation * uniform_group.rotation * uniform_group.scaling;

	position = group_transformation * instance_transformation * bones_transformation * vec4(in_position, 1.f);

	pass_position = position.xyz;
	pass_normal = vec3(uniform_group.rotation * uniform_instance.rotation * bones_transformation * vec4(in_normal, 0.f));
	pass_UV = in_UV;
	pass_distance_to_camera = length(uniform_view * position);

	gl_Position = uniform_projection * uniform_view * position;
}