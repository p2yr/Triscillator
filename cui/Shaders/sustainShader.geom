#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 FragColor[];

out vec3 FinalColor;

uniform float xMovementAtk;
uniform float yMovementSus;
uniform float offset;

void main() {
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        if (i == 1) {
            gl_Position.y += yMovementSus;
        }
        if (i == 0 || i == 1) {
            gl_Position.x += xMovementAtk;
        }
        FinalColor = FragColor[i];
        EmitVertex();
    }
    EndPrimitive(); 

    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        gl_Position.x = gl_Position.x * (-1) + offset;
        if (i == 2 || i == 0) {
            gl_Position.y += yMovementSus;
        }
        if (i == 2)
            gl_Position.x += xMovementAtk;
        FinalColor = FragColor[i];
        EmitVertex();
    }
    EndPrimitive();
}
