#version 330 core

in vec4 vPosition;

uniform mat4 modelView;
uniform mat4 projection;


void main()
{
	gl_Position = projection * modelView * vPosition;
}