#version 330 core

in vec2				pass_UV;
out vec4			out_color;

uniform sampler2D	uniform_texture;
uniform vec3		uniform_color;
uniform int			uniform_use_texture;

void main()
{
	out_color =
		uniform_use_texture == 1 ?
		texture(uniform_texture, pass_UV) :
		vec4(uniform_color, 1.f);
}