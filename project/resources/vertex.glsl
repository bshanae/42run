#version 330 core

layout(location = 0) in vec3	in_position;
layout(location = 1) in vec3	in_normal;
layout(location = 2) in vec2	in_UV;

out vec2						pass_UV;

uniform mat4					uniform_projection;
uniform mat4					uniform_view;

void							main()
{
	gl_Position = uniform_projection * uniform_view * vec4(in_position, 1.f);
	pass_UV = in_UV;

}