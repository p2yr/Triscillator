#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 FragColor[]; // Input color from the vertex shader

out vec3 FinalColor; // Output color to the fragment shader

uniform float xMovementRel;
uniform float yMovementSus;

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        if (i == 2) {
            gl_Position.x += xMovementRel;
        }
        if(i == 1){
            gl_Position.y += yMovementSus;
        }
        FinalColor = FragColor[i];
        EmitVertex();
    }
    EndPrimitive();
}