#version 330 core

in vec3 vPosition;
in vec2 vTexture;

uniform mat4 ctm;

out vec2 textureCoord;

void main()
{
	gl_Position = ctm * vec4(vPosition, 1.f);
	textureCoord = vTexture;
}

