#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
} fs_in;

uniform sampler2D u_diffuse;
uniform vec3 u_ambientClr;

void main()
{
    vec4 clr =  vec4(fs_in.Normal,1);// texture(u_diffuse, fs_in.TexCoords) * vec4(u_ambientClr,1);
    if(clr.a < 0.1) discard;
    //FragColor = vec4(fs_in.TexCoords.x,fs_in.TexCoords.y,1,1);
    FragColor = vec4(clr);
}