#version 330 core
in vec3 FinalColor; // Input color from the geometry shader

out vec4 FragColor; // Output color

void main() {
    FragColor = vec4(FinalColor, 1.0);
}