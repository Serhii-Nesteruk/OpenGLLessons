#version 460 core

// in vec2 fragCoords;

out vec4 FragColor;
	
in vec3 ioColor;
in vec2 ioTexCoords;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture, ioTexCoords);
}