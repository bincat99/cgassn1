#version 400

layout(location = 0) in vec3 position;

uniform mat4 MVP;
uniform mat4 ani;



void main()
{
	gl_Position = MVP * ani*vec4(position,1.0);
}