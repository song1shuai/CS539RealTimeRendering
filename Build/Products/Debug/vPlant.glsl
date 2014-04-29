#version 400

layout(location = 0) in   vec3 vPos;
layout(location = 1) in   vec2 vTexCoord;
layout(location = 2 ) in  vec3 vNormals;



uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 nv;
uniform vec3 lightPos;
uniform mat4 lightSPV;




out  vec3 fLightDir;
out  vec3 fViewDir;
out  vec3 fNormals;
out  vec4 ShadowPos;
out  vec2 fTexCoord;



void main(void)
{
    
    fTexCoord  = vTexCoord;
    vec3 posInEye = vec3(mv * vec4(vPos,1.0));
    vec4 lightIneye = mv * vec4(lightPos,1.0);
    fLightDir = normalize(  lightIneye.xyz - posInEye);
    fViewDir  = (-posInEye);
    fNormals= vec3( mv*vec4(vNormals,0.0));
    
    ShadowPos = lightSPV*model*vec4(vPos,1.0);
    
    gl_Position=mvp*vec4(vPos,1.0);;
    
    
}
