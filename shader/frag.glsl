#version 330 core

uniform vColor;
out vec4 color;

void main()
{
	color = vColor;
}