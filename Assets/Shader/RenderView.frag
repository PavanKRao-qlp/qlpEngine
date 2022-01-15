#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D u_diffuse;
uniform sampler2D u_position;
uniform sampler2D u_normal;

struct PointLight {
vec3 color; // 16 0
vec3 position;// 16 16
float range; //4 32
float[3] attenuation;
};

layout (std140) uniform LightsBlock {
    PointLight pointLights[10]; //36*10 0
};

vec3 CalcLighting(PointLight light){
    vec3 noraml = texture(u_normal, fs_in.TexCoords).xyz;
    noraml = normalize(noraml);
    vec3 pixelWpos = texture(u_position, fs_in.TexCoords).xyz;
    vec3 lightDir = normalize(light.position - pixelWpos);
    float diff = max(dot(noraml, lightDir), 0.0);
    vec3 lightColor = light.color * diff;
    float distance    = length(light.position -  pixelWpos);
    float attenuation = 1.0 / (1 + 0.007f * distance + 0.0002f * (distance * distance));    
    lightColor   *= attenuation;    
    return lightColor;
}

void main() {
    vec4 diffuse =   texture(u_diffuse, fs_in.TexCoords);  
    if(diffuse.a < 0.1) discard;
   
    vec4 light = vec4(0);
       for(int i = 0; i <= 10 ; i++) { 
        if(pointLights[i].color != vec3(0)) {
            light += vec4(CalcLighting(pointLights[i]),1);
            }else break;
       }
       FragColor = diffuse * light;
}
