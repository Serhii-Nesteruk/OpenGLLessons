#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
	
uniform vec2 uWindowSize;
uniform mat4 uModelMatrix;
uniform mat4 uCameraMatrix;

out vec2 ioTexCoords;

void main()
{
	ioTexCoords = aTexCoords;
	vec4 finalPosition = (uCameraMatrix * uModelMatrix * vec4(aPos.x, aPos.y, 0, 1)) / vec4(uWindowSize.x, uWindowSize.y, 0, 1);
	gl_Position = vec4(finalPosition.x, finalPosition.y, 0.0, 1.0);
}