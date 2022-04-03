#version 330 core
out vec4 FragColor;
layout (location = 0) out vec4 Albedo;
layout (location = 1) out vec4 Position;
layout (location = 2) out vec4 Normal;
layout (location = 3) out vec4 NormalMap;

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragWPos;
} fs_in;

uniform sampler2D u_diffuse;
uniform sampler2D u_normalMap;
uniform vec3 u_ambientClr;

void main() {
    vec4 clr =  texture(u_diffuse, fs_in.TexCoords) * vec4(u_ambientClr,1);
   if(clr.a < 0.1) discard;
    Albedo =  clr ; 
    Position =  vec4(fs_in.FragWPos,1);
    Normal =  vec4(fs_in.Normal,1); //  vec4(normalize(fs_in.Normal),1);
    NormalMap =  texture(u_normalMap, fs_in.TexCoords) * vec4(u_ambientClr,1);
}
