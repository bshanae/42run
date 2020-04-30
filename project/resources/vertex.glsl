#version 400 core

in vec3				in_position;
in vec4				in_color;

out vec4			pass_color;

uniform mat4		uniform_projection;
uniform mat4		uniform_view;

void				main()
{
	pass_color = in_color;

	gl_Position = uniform_projection * uniform_view * vec4(in_position, 1.f);
}