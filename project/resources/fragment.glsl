#version 330 core

in vec2				pass_UV;

out vec4			final_color;

uniform sampler2D	uniform_texture;

void				main()
{
	final_color = texture(uniform_texture, pass_UV);
}