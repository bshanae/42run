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
	int					type[SHARED_LIGHTS_CAPACITY];
	vec3				data[SHARED_LIGHTS_CAPACITY];
	vec3				color[SHARED_LIGHTS_CAPACITY];
	float				intensity[SHARED_LIGHTS_CAPACITY];
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

vec3					calculate_diffuse(vec3 normal, vec3 direction_to_light)
{
	vec3				material_color;

	material_color = uniform_material.unite.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	float				intensity = dot(normal, direction_to_light);

	return (material_color * intensity);
}

vec3					calculate_specular(vec3 normal, vec3 direction_to_light)
{
	vec3				material_factor;

	material_factor = uniform_material.unite.specular;
	if (uniform_material.textures.specular.is_valid)
		material_factor *= texture(uniform_material.textures.specular.value, pass_UV).r;

	vec3				view_direction = normalize(uniform_camera_position - pass_position);
	vec3				reflection_direction = reflect(-direction_to_light, normal);
	float				intensity = dot(view_direction, reflection_direction);

	intensity = pow(max(intensity, 0.0), 512);

	return (material_factor * intensity);
}

float					calculate_attenuation(float distance)
{
	return
	(
		1.0f /
		(
			SHARED_ATTENUATION_CONSTANT +
			SHARED_ATTENUATION_LINEAR * distance +
			SHARED_ATTENUATION_QUADRATIC * (distance * distance)
		)
	);
}


void					main()
{
	final_color = vec4(0, 0, 0, uniform_material.unite.alpha);
//	final_color.rgb += calculate_ambient();

	vec3				normal = normalize(pass_normal);
	vec3				direction_to_light;
	float				distance_to_light;
	float				attenuation;

	for (int i = 0; i < uniform_light.size; i++)
	{
//						w = 0.0 -> directional light
//						w = 1.0 -> point light

		if (uniform_light.type[i] == SHARED_LIGHT_TYPE_DIRECTIONAL)
		{
			direction_to_light = normalize(uniform_light.data[i]);
			attenuation = 1.0f;
		}
		else if (uniform_light.type[i] == SHARED_LIGHT_TYPE_POINT)
		{
			direction_to_light = normalize(uniform_light.data[i] - pass_position);
			distance_to_light = length(uniform_light.data[i] - pass_position);
			attenuation = calculate_attenuation(distance_to_light);
//			attenuation = 1.0f;
		}

		final_color.rgb += attenuation * uniform_light.color[i] * uniform_light.intensity[i] * calculate_diffuse(normal, direction_to_light);
		final_color.rgb += attenuation * uniform_light.color[i] * uniform_light.intensity[i] * calculate_specular(normal, direction_to_light);
	}

	final_color.rgb += uniform_material.unite.emission;

//	DEBUG


	vec3 x = uniform_camera_position;
}