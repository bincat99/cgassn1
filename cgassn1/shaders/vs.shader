#version 400

in vec4 position;
in vec4 color_in;
out vec4 color_out;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = view * model * position;
	color_out = color_in;
}