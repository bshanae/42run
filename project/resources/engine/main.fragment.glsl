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

struct					light
{
	int					type;
	vec3				data;
	vec3				color;
	float				power;
};

uniform struct
{
	vec3				camera_position;

	int					lights_size;
	light				lights[SHARED_LIGHTS_CAPACITY];
}						uniform_scene;

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

	vec3				view_direction = normalize(uniform_scene.camera_position - pass_position);
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

///////////////////////////////////////////////////////////////////////////////
//						MAIN
///////////////////////////////////////////////////////////////////////////////

void					main()
{
	final_color = vec4(0, 0, 0, uniform_material.unite.alpha);
//	final_color.rgb += calculate_ambient();

	vec3				normal = normalize(pass_normal);
	vec3				direction_to_light;
	float				distance_to_light;
	float				attenuation;

	for (int i = 0; i < uniform_scene.lights_size; i++)
	{
		if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_DIRECTIONAL)
		{
			direction_to_light = normalize(-uniform_scene.lights[i].data);
			attenuation = 1.0f;
		}
		else if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_POINT)
		{
			direction_to_light = normalize(uniform_scene.lights[i].data - pass_position);
			distance_to_light = length(uniform_scene.lights[i].data - pass_position);
			attenuation = calculate_attenuation(distance_to_light);
		}

		final_color.rgb += attenuation * uniform_scene.lights[i].color * uniform_scene.lights[i].power * calculate_diffuse(normal, direction_to_light);
		final_color.rgb += attenuation * uniform_scene.lights[i].color * uniform_scene.lights[i].power * calculate_specular(normal, direction_to_light);
	}

	final_color.rgb += uniform_material.unite.emission;
}