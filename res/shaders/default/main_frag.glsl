/*#version 460 core

in vec3 color;
out vec4 frag_color;

void main() {
   frag_color = vec4(color, 1.0);
}*/

#version 330 core
in vec3 ourColor;
in vec2 ourPos;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
   FragColor = texture(u_texture, ourPos);
}