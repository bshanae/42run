#version 400 core

in vec4				pass_color;

out vec4			final_color;

void				main()
{
	final_color = pass_color;
}