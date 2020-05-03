#version 330 core

in vec2					pass_UV;

out vec4				final_color;

struct					texture_wrap
{
	bool				is_valid;
	sampler2D			value;
};

uniform struct
{
	struct
	{
		vec3			ambient;
		vec3			diffuse;
		vec3			specular;
	}					colors;

	struct
	{
		texture_wrap	diffuse;
	}					textures;
}						uniform_material;

uniform sampler2D		uniform_texture;

void					main()
{
	vec3				lol_0 = uniform_material.colors.ambient;
	vec3				lol_1 = uniform_material.colors.diffuse;
	vec3				lol_2 = uniform_material.colors.specular;
	vec4				lol_4 = texture(uniform_texture, pass_UV);
	bool				lol_5 = uniform_material.textures.diffuse.is_valid;

	if (lol_5)
		final_color = lol_4;
	else
		final_color = vec4(1, 1, 1, 1);
}