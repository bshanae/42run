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
		vec3			emission;
		float			alpha;
	}					unite;

	struct
	{
		texture_wrap	ambient;
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

vec3					calculate_ambient()
{
	vec3				material_color;

	if (uniform_material.textures.ambient.is_valid)
		return (texture(uniform_material.textures.ambient.value, pass_UV).rgb);
	else
		return (uniform_material.unite.ambient);
}

#define DIFFUSE_FLOOR	0.3

vec3					calculate_diffuse(vec3 normal, vec3 light_direction)
{
	vec3				material_color;

	material_color = uniform_material.unite.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	float				intensity = max(dot(normal, light_direction), DIFFUSE_FLOOR);

	return (material_color * intensity);
}

#define SPECULAR_FLOOR	0.0

vec3					calculate_specular(vec3 normal, vec3 light_direction)
{
	vec3				material_factor;

	material_factor = uniform_material.unite.specular;
	if (uniform_material.textures.specular.is_valid)
		material_factor *= texture(uniform_material.textures.specular.value, pass_UV).r;

	vec3				view_direction = normalize(uniform_light.camera - pass_position);
	vec3				reflect_direction = reflect(-light_direction, normal);
	float				intensity = dot(view_direction, reflect_direction);

	intensity = max(intensity, SPECULAR_FLOOR);
	intensity = pow(intensity, 512);

	return (material_factor * intensity);
}

void					main()
{
	vec3				normal = normalize(pass_normal);
	vec3				light_direction = normalize(uniform_light.position - pass_position);

	final_color = vec4(0, 0, 0, uniform_material.unite.alpha);
//	final_color.rgb += calculate_ambient();
	final_color.rgb += calculate_diffuse(normal, light_direction);
	final_color.rgb += calculate_specular(normal, light_direction);
	final_color.rgb += uniform_material.unite.emission;

//	final_color = vec4(pass_UV, 0, 1);
//	final_color = vec4(uniform_material.textures.specular.is_valid, 0, 0, 1);
}