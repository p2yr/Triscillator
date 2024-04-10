#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
out vec3 FragColor;

uniform float xMovementAtk;
uniform float xMovement;
uniform float yMovement;

void main()
{
   gl_Position = vec4(aPos.x + xMovement + xMovementAtk, aPos.y + yMovement, aPos.z, 1.0);
   FragColor = aColor;
}