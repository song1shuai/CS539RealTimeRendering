#version 400

layout(location = 0) in  vec3 vPos;
layout(location = 1) in  vec2 vTexCoord;
layout(location = 2) in  vec3 vNormals;
layout(location = 3) in  vec3 vTangent;
out  vec2 fTexCoord;

//light attribute

out  vec3 fLightDir;
out  vec3 fViewDir;
out  vec3 fNormals;
out  vec4 ShadowPos;

//In world space;
uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 nv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform mat4 lightSPV;





void main(void)
{
    
    vec3 norm = normalize( nv * vNormals );
    
    vec3 tang = normalize( nv * vec3(vTangent) );
    // Compute the binormal
    vec3 binormal = normalize( cross( norm, tang ));
    // Matrix for transformation to tangent space
    mat3 toObjectLocal = mat3(
                              tang.x, binormal.x, norm.x,
                              tang.y, binormal.y, norm.y,
                              tang.z, binormal.z, norm.z
                              );
    
    vec3 posInEye = vec3(mv * vec4(vPos,1.0));
    vec4 lightIneye = view * vec4(lightPos,1.0);
    
    fLightDir = normalize(toObjectLocal * (lightIneye.xyz - posInEye));
    fViewDir  = toObjectLocal*(-posInEye);
    
    
    fTexCoord  = vTexCoord;
    ShadowPos = lightSPV*model*vec4(vPos,1.0);
    gl_Position=mvp*vec4(vPos,1.0);;
    

    

}
