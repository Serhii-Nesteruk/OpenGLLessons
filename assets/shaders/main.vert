#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
	
uniform vec2 uWindowSize;

out vec2 ioTexCoords;

void main()
{
	ioTexCoords = aTexCoords;
	vec2 finalPosition = aPos / uWindowSize;
	gl_Position = vec4(finalPosition.x, finalPosition.y, 0.0, 1.0);
}