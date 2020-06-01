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

uniform vec3			uniform_camera_position;

uniform struct
{
	int					size;
	vec4				direction_or_position[SHARED_LIGHTS_CAPACITY];
	vec3				color[SHARED_LIGHTS_CAPACITY];
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

vec3					calculate_diffuse(vec3 normal, vec3 light_direction)
{
	vec3				material_color;

	material_color = uniform_material.unite.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	float				intensity = dot(normal, light_direction);

	return (material_color * intensity);
}

vec3					calculate_specular(vec3 normal, vec3 light_direction)
{
	vec3				material_factor;

	material_factor = uniform_material.unite.specular;
	if (uniform_material.textures.specular.is_valid)
		material_factor *= texture(uniform_material.textures.specular.value, pass_UV).r;

	vec3				view_direction = normalize(uniform_camera_position - pass_position);
	vec3				reflect_direction = reflect(-light_direction, normal);
	float				intensity = dot(view_direction, reflect_direction);

	intensity = pow(intensity, 512);

	return (material_factor * intensity);
}

void					main()
{
	final_color = vec4(0, 0, 0, uniform_material.unite.alpha);
//	final_color.rgb += calculate_ambient();

	vec3				normal = normalize(pass_normal);
	vec3				light_direction;

	for (int i = 0; i < uniform_light.size; i++)
	{
//						w = 0.0 -> directional light
//						w = 1.0 -> point light

		if (uniform_light.direction_or_position[i].w == 0.0)
			light_direction = normalize(uniform_light.direction_or_position[i].xyz);
		else if (uniform_light.direction_or_position[i].w == 1.0)
			light_direction = normalize(uniform_light.direction_or_position[i].xyz - pass_position);

		final_color.rgb += calculate_diffuse(normal, light_direction);
//		final_color.rgb += calculate_specular(normal, light_direction);
	}

	final_color.rgb += uniform_material.unite.emission;

//	DEBUG


	vec3 x = uniform_camera_position;
}