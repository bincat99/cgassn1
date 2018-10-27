#version 400

in vec4 position;
in vec4 color_in;
out vec4 color_out;
uniform mat4 transform;

void main()
{
	gl_Position = transform * position;
	color_out = color_in;
}