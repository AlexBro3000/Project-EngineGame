#version 460 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texture;
layout (location = 2) in vec3 vertex_normal;

out vec3 out_curent_position;
out vec2 out_texture_position;
out vec3 out_normal;

uniform mat4 model;
uniform mat4 projview;

void main()
{
	out_curent_position  = vec3(model * vec4(vertex_position, 1.0));
	out_texture_position = vertex_texture;
	out_normal           = vertex_normal;

	gl_Position = projview * vec4(out_curent_position, 1.0);
}
