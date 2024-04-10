#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 FragColor[]; // Input color from the vertex shader

out vec3 FinalColor; // Output color to the fragment shader

uniform float xMovement;
uniform float yMovement;

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        if (i != 0) {
            gl_Position.x += xMovement;
            gl_Position.y += yMovement;
        }
        FinalColor = FragColor[i];
        EmitVertex();
    }
    EndPrimitive();
}