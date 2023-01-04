#version 330 core

in vec3 fragmentColor;
out vec4 color;

in vec2 TexCoord;

uniform sampler2D blockTexture;

void main(){
    color = texture(blockTexture, TexCoord);

    
}