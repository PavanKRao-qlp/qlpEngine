#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_PV;
uniform mat4 u_M;

out VS_OUT {
    vec2 TexCoords;
} vs_out;


void main()
{
    gl_Position =  vec4(aPos, 1.0); 
    vs_out.TexCoords = aTexCoord;
}