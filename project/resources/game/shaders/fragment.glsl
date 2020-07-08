///////////////////////////////////////////////////////////////////////////////
//						IN-OUT
///////////////////////////////////////////////////////////////////////////////

in vec3					pass_position;
in vec3					pass_normal;
in vec2					pass_UV;
in float				pass_distance_to_camera;

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

	vec3				parameter_a;
	vec3				parameter_b;
	float				parameter_c;
	float				parameter_d;

	vec3				color;
	float				power;
};

uniform struct
{
	vec3				camera_position;

	int					lights_size;
	light				lights[SHARED_LIGHTS_CAPACITY];
}						uniform_scene;

uniform struct
{
	float				density;
	float				gradient;
	int					use;
	vec3				background;
}						uniform_fog;

///////////////////////////////////////////////////////////////////////////////
//						FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

vec3					clamp_vec3(vec3 value, vec3 min, vec3 max)
{
	return
	(
		vec3
		(
			clamp(value.x, min.x, max.x),
			clamp(value.y, min.y, max.y),
			clamp(value.z, min.z, max.z)
		)
	);
}

vec3					calculate_ambient()
{
	vec3				material_color;

	material_color = uniform_material.unite.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	return (material_color);
}

vec3					calculate_diffuse(vec3 normal, vec3 direction_to_light)
{
	vec3				material_color;
	float				intensity;

	material_color = uniform_material.unite.diffuse;
	if (uniform_material.textures.diffuse.is_valid)
		material_color *= texture(uniform_material.textures.diffuse.value, pass_UV).rgb;

	intensity = dot(normal, direction_to_light);
	intensity = clamp(intensity, 0, 1);
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

float					calculate_point_attenuation(int i, float distance)
{
	return
	(
		1.0f /
		(
			SHARED_ATTENUATION_CONSTANT +
			uniform_scene.lights[i].parameter_c * distance +
			uniform_scene.lights[i].parameter_d * (distance * distance)
		)
	);
}

float					calculate_projector_attenuation(int i, float theta)
{
	float				epsilon = uniform_scene.lights[i].parameter_c - uniform_scene.lights[i].parameter_d;
	float				attenuation = (theta - uniform_scene.lights[i].parameter_c) / epsilon;

	attenuation = clamp(attenuation, 0.f, 1.f);
	return (attenuation);
}

vec3					process_light(vec3 normal, int i)
{
	vec3				direction_to_light;
	float				distance_to_light;

	float				attenuation = 1.f;

	vec3				diffuse = vec3(0);
	vec3				specular = vec3(0);

	if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_AMBIENT)
		return (calculate_ambient() * uniform_scene.lights[i].color * uniform_scene.lights[i].power);
	else if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_DIRECTIONAL)
		direction_to_light = normalize(-uniform_scene.lights[i].parameter_a);
	else if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_POINT)
	{
		direction_to_light = normalize(uniform_scene.lights[i].parameter_a - pass_position);
		distance_to_light = length(uniform_scene.lights[i].parameter_a - pass_position);
		attenuation = calculate_point_attenuation(i, distance_to_light);
	}
	else if (uniform_scene.lights[i].type == SHARED_LIGHT_TYPE_PROJECTOR)
	{
		float			theta;

		direction_to_light = normalize(uniform_scene.lights[i].parameter_a - pass_position);
		theta = dot(direction_to_light, normalize(-uniform_scene.lights[i].parameter_b));

		if (theta <= uniform_scene.lights[i].parameter_c)
			return (vec3(0));

		attenuation = calculate_projector_attenuation(i, theta);
	}

	diffuse = calculate_diffuse(normal, direction_to_light);
	specular = calculate_specular(normal, direction_to_light);

	diffuse *= attenuation * uniform_scene.lights[i].color * uniform_scene.lights[i].power;
	specular *= attenuation * uniform_scene.lights[i].color * uniform_scene.lights[i].power;

	return (diffuse + specular);
}

///////////////////////////////////////////////////////////////////////////////
//						MAIN
///////////////////////////////////////////////////////////////////////////////

void					main()
{
	final_color = vec4(0, 0, 0, uniform_material.unite.alpha);

	vec3				normal = normalize(pass_normal);
	float				visibility;

	for (int i = 0; i < uniform_scene.lights_size; i++)
		final_color.rgb += process_light(normal, i);

	final_color.rgb += uniform_material.unite.emission;

	if (uniform_fog.use == 1)
	{
		visibility = exp(-pow(pass_distance_to_camera * uniform_fog.density, uniform_fog.gradient));
		visibility = clamp(visibility, 0.f, 1.f);
		final_color = mix(vec4(uniform_fog.background, 1.f), final_color, visibility);
	}
}