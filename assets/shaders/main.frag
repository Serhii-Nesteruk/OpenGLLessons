#version 460 core

out vec4 FragColor;
	
in vec2 ioTexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, ioTexCoords), texture(texture2, ioTexCoords), 0.2);
}