#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
} fs_in;

out vec4 frag_color;

uniform vec4 tint;
uniform sampler2D tex;

void main(){
    //TODO: Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color and with the texture color 
    //frag_color = vec4(0, 0, 0, 1);
    //Done:Sandra Hany
    //texture2D(tex,fs_in.tex_coord)->texture color 
    //fs_in.color->vertex color
    frag_color=texture(tex,fs_in.tex_coord)*fs_in.color; 
}
