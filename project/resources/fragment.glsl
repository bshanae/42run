#version 330 core

///////////////////////////////////////////////////////////////////////////////
//						IN-OUT
///////////////////////////////////////////////////////////////////////////////

in vec3					pass_position;
in vec3					pass_normal;
in vec2					pass_UV;

out vec4				final_color;

///////////////////////////////////////////////////////////////////////////////
//						UNIFORM
///////////////////////////////////////////////////////////////////////////////

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
		texture_wrap	specular;
	}					textures;
}						uniform_material;

uniform struct
{
	vec3				camera;
	vec3				position;
	float				intensity;
}						uniform_light;

///////////////////////////////////////////////////////////////////////////////
//						FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

#define DIFFUSE_FLOOR	0.05
#define SPECULAR_FLOOR	0.0

vec3					calculate_diffuse(vec3 normal, vec3 light_direction)
{
	vec3				material_color;

	material_color = uniform_material.colors.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	float				intensity = max(dot(normal, light_direction), DIFFUSE_FLOOR);

	return (material_color * intensity);
}

vec3					calculate_specular(vec3 normal, vec3 light_direction)
{
	vec3				material_color;

	material_color = uniform_material.colors.specular;
	if (uniform_material.textures.specular.is_valid)
		material_color *= texture(uniform_material.textures.specular.value, pass_UV).r;


	vec3				view_direction = normalize(uniform_light.camera - pass_position);
	vec3				reflect_direction = reflect(-light_direction, normal);
	float				intensity = dot(view_direction, reflect_direction);

	intensity = max(intensity, SPECULAR_FLOOR);
	intensity = pow(intensity, 32);

	return (material_color * intensity);
}

void					main()
{
	vec3				normal = normalize(pass_normal);
	vec3				light_direction = normalize(uniform_light.position - pass_position);

	final_color = vec4(uniform_material.colors.ambient, 0);
	final_color += vec4(calculate_diffuse(normal, light_direction), 0);
	final_color += vec4(calculate_specular(normal, light_direction), 0);
	final_color.a = 1;

//	final_color = vec4(pass_UV, 0, 1);
}