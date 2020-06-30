#version 330 core

layout (location = 0) in vec3	coordinate;
layout (location = 1) in vec2	UV;
out vec2						pass_UV;

uniform mat4					uniform_projection;
uniform mat4					uniform_scaling;
uniform mat4					uniform_translation;

void							main()
{
	pass_UV = UV;
	gl_Position = uniform_projection * uniform_translation * uniform_scaling * vec4(coordinate, 1);
}