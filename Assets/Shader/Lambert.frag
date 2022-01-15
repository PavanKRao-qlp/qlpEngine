#version 330 core
out vec4 FragColor;
layout (location = 0) out vec4 Albedo;
layout (location = 1) out vec4 Position;
layout (location = 2) out vec4 Normal;
layout (location = 3) out vec4 ForwardPass;

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragWPos;
} fs_in;

uniform sampler2D u_diffuse;
uniform vec3 u_ambientClr;

struct PointLight {
vec3 color; // 16 0
vec3 position;// 16 16
float range; //4 32
float[3] padding;
};

layout (std140) uniform LightsBlock {
    PointLight pointLights[10]; //36*10 0
};

vec3 CalcLighting(PointLight light){
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(light.position - fs_in.FragWPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.color * diff;
    float distance    = length(light.position - fs_in.FragWPos);
    //float attenuation = 1.0 / (1 + 0.07f * distance + 0.017f * (distance * distance));    
    //diffuse   *= attenuation;    
    return diffuse;
}

void main() {
    vec4 clr =  texture(u_diffuse, fs_in.TexCoords) * vec4(u_ambientClr,1);
   if(clr.a < 0.1) discard;
  
   vec4 light = vec4(0);
   for(int i = 0; i <= 10 ; i++) { 
        if(pointLights[i].color != vec3(0)) {
            light += vec4(CalcLighting(pointLights[i]),1);
            }else{
            break;
            }
    }
    ForwardPass = clr * light;
    Albedo =  clr ; 
    Position =  vec4(fs_in.FragWPos,1);
    Normal =  vec4(fs_in.Normal,1); //  vec4(normalize(fs_in.Normal),1);
}
