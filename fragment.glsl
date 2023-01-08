#version 330 core

out vec4 color;

in vec2 TexCoord;

uniform sampler2D blockTexture;

void main(){
    color = texture(blockTexture, TexCoord);

    
}