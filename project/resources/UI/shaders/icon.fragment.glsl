#version 330 core

in vec2				pass_UV;
out vec4			out_color;

uniform sampler2D	uniform_texture;

void main()
{
	out_color = texture(uniform_texture, pass_UV);
}