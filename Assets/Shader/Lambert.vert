#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_PV;
uniform mat4 u_M;

out VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragWPos;
} vs_out;


void main()
{
    gl_Position =  u_PV  * u_M * vec4(aPos, 1.0); 
    vs_out.FragWPos = (u_M * vec4(aPos, 1.0)).xyz; 
    vs_out.TexCoords = aTexCoord;
    vs_out.Normal =  mat3(transpose(inverse(u_M))) * aNormal;
}