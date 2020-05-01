#version 400 core

in vec3				in_position;
in vec3				in_normal;
in vec2				in_UV;

uniform mat4		uniform_projection;
uniform mat4		uniform_view;

void				main()
{
	gl_Position = uniform_projection * uniform_view * vec4(in_position, 1.f);
}