#version 330

uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
uniform int mixer;

in vec2 texcoord;


// Get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

uniform vec3 sun_position;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int type_of_light;
uniform float cut_off_angle;

layout(location = 0) out vec4 out_color;
uniform int is_sun;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

	vec3 sunL = normalize(sun_position - world_position);
	vec3 sunH = normalize(sunL + V);
	vec3 sunR = normalize(reflect(sunL, world_normal));

	// Define ambient light component
	vec3 ambient_light = vec3(0.25, 0.25, 0.25);

	// Compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);
	float sun_diffuse_light = material_kd * max(dot(normalize(N), sunL), 0.f);

	// Compute specular light component
	float specular_light = 0.f;
	float sun_specular_light = 0.f;

	if (diffuse_light > 0.f)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	if (sun_diffuse_light > 0.f)
	{
		sun_specular_light = material_ks * pow(max(dot(N, sunH), 0), material_shininess);
	}

	// Compute light
	vec3 light = vec3(0,0,0);
	
	float cut_off_rad		= radians(cut_off_angle);
	float spot_light		= dot(-L, light_direction);
	float spot_light_limit	= cos(cut_off_rad);
		
	if (spot_light > spot_light_limit)
	{	 
		// Quadratic attenuation
		float linear_att		= (spot_light - spot_light_limit) / (1.f - spot_light_limit);
		float light_att_factor	= linear_att * linear_att;
		light					= vec3(1, 1, 1 ) * light_att_factor * (diffuse_light + specular_light);
	}

	float d						= distance(sun_position, world_position);
	float attenuation_factor	= 1.f / max(d * d, 1.f);
	//light += ambient_light + vec3(1, 1, 1) * attenuation_factor * (sun_diffuse_light + sun_specular_light);		
	//light += ambient_light;
	if (is_sun == 1) {
		ambient_light = vec3(1, 1, 1);
	}
	light += ambient_light + vec3(1, 1, 1) * 1 * (sun_diffuse_light + sun_specular_light);

	// Write pixel out color
	vec3 colour = object_color * light;
	vec4 color1 = texture2D(texture_1, texcoord);
	vec4 color2 = texture2D(texture_2, texcoord);
	
	vec4 color;
	if(mixer == 1)
		color = mix(color1, color2, 0.5f);
	else 
		color = color1;

	if(color.a < 0.5f)
		discard;

	out_color = vec4(light, 1) * color;
}