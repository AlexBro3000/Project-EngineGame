#version 460 core
in vec3 out_curent_position;
in vec2 out_texture_position;
in vec3 out_normal;

out vec4 frag_color;

uniform sampler2D u_texture_0;
uniform vec3 position;
uniform vec4 light_color;
uniform vec3 light_position;

void main()
{
	float ambient        = 0.20f;
	float specular_light = 0.50f;

	// diffuse lighting
	vec3 normal          = normalize(out_normal);
	vec3 light_direction = normalize(light_position - out_curent_position);
	float diffuse        = max(dot(normal, light_direction), 0.0f);
	
	// specular lighting
	vec3 view_direction       = normalize(position - out_curent_position);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float spec_amount         = pow(max(dot(view_direction, reflection_direction), 0.0f), 8);
	float specular            = spec_amount * specular_light;

	// outputs final color
	frag_color = texture(u_texture_0, out_texture_position) * light_color * (diffuse + ambient + specular);
}

