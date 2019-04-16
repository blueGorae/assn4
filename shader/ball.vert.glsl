#version 330 core

in vec3 vPosition;

uniform mat4 modelView;
uniform mat4 projection;


void main()
{
	gl_Position = projection * modelView * vec4(vPosition, 1.f);
}