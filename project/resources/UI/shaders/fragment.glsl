#version 330 core

in vec2				pass_UV;
out vec4			out_color;

uniform sampler2D	uniform_texture;
uniform vec3		uniform_color;

void main()
{
	vec4			sampled;

	sampled = vec4(1, 1, 1, texture(uniform_texture, pass_UV).r);
	out_color = vec4(uniform_color, 1) * sampled;

//	out_color = vec4(texture(uniform_texture, pass_UV).rgb, 1);
//	out_color = vec4(pass_UV.xy, 0, 1);
//	out_color = vec4(1, 0, 0, 1);
}