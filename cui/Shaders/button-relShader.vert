#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
out vec3 FragColor;

uniform float xMovement;

void main()
{
   gl_Position = vec4(aPos.x + xMovement, aPos.y, aPos.z, 1.0);
   FragColor = aColor;
}