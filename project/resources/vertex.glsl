#version 330 core

///////////////////////////////////////////////////////////////////////////////
//								IN-OUT
///////////////////////////////////////////////////////////////////////////////

layout(location = 0) in vec3	in_position;
layout(location = 1) in vec3	in_normal;
layout(location = 2) in vec2	in_UV;

out vec3						pass_position;
out vec3						pass_normal;
out vec2						pass_UV;

///////////////////////////////////////////////////////////////////////////////
//								UNIFORM
///////////////////////////////////////////////////////////////////////////////

uniform mat4					uniform_projection;
uniform mat4					uniform_view;

void							main()
{
	pass_position = in_position;
	pass_normal = in_normal;
	pass_UV = in_UV;

	gl_Position = uniform_projection * uniform_view * vec4(in_position, 1.f);
}