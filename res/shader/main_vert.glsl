/* #version 460 core

layout(location = 0) in vec3 vertex_position;
// layout(location = 1) in vec3 vertex_color;
out vec3 color;

void main() {
   color = vec3(1.0f, 0.5f, 0.2f); // vertex_color;
   gl_Position = vec4(vertex_position, 1.0);
}*/

#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;

out vec3 color;

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
	color = vertex_color;
}