#version 330 core

out vec4 out_color;

in vec2 TexCoord;
in float light_level;

uniform sampler2D blockTexture;

void main(){
    vec4 color = texture(blockTexture, TexCoord);

    color.x *= light_level;
    color.y *= light_level;
    color.z *= light_level;

    out_color = color;
    if(out_color.a == 0) discard;
}