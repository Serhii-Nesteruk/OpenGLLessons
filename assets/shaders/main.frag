#version 330 core

out vec4 FragColor;
	
in vec3 ioColor;
	
void main()
{
	FragColor = vec4(ioColor.r, ioColor.g, ioColor.b, 1.0f);
}