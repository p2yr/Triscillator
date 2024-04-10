#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    if(texColor.a < 0.1)
        discard;
    if(texColor.a < 0.6){
        texColor.r = ourColor[0]/1.5;
        texColor.g = ourColor[1]/1.5;
        texColor.b = ourColor[2]/1.5;
    }
    if(texColor.a < 0.3){
        texColor.r = ourColor[0]/2;
        texColor.g = ourColor[1]/2;
        texColor.b = ourColor[2]/2;
    }
    FragColor = texColor;
}