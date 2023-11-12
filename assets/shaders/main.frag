#version 460 core

out vec4 FragColor;
	
in vec2 ioTexCoords;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture, ioTexCoords) + vec4(1, 0,0, 0.5);
}