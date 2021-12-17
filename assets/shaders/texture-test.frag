#version 330 core

in Varyings {
    vec3 position;
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
} fs_in;

out vec4 frag_color;

uniform sampler2D tex;

void main(){
    //TODO: Change the following line to read the fragment color
    //Done:Sandra Hany
    // from the texture at the received texture coordinates
    //frag_color = vec4(0, 0, 0, 1);
    //texture -> Normalised version because it isnot usually 1:1 mapping
    //To sample the color of a texture we use texture function that takes as its first argument a texture sampler and as its second argument the corresponding texture coordinates. The texture function then samples the corresponding color value using the texture parameters we set earlier. The output of this fragment shader is then the (filtered) color of the texture at the (interpolated) texture coordinate.
    frag_color=texture(tex,fs_in.tex_coord);
   //frag_color=texelFetch(tex,tex_coord.xy,0)
}
