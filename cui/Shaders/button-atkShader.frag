#version 330 core
in vec3 FragColor; // Input color from the geometry shader

out vec4 FinalColor; // Output color

void main() {
    FinalColor = vec4(FragColor, 1.0);
}