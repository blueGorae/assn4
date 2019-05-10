#version 330 core

uniform vec4 vColor;
in vec2 textureCoord;

uniform sampler2D Texture;
out vec4 color;

void main()
{
	color = texture(Texture, textureCoord);
}