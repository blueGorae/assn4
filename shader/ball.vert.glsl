#version 330 core

in vec3 vPosition;

uniform mat4 ctm;

void main()
{
	gl_Position = ctm * vec4(vPosition, 1.f);
}