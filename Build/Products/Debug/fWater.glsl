#version 400
out vec4 fragColor;
in vec3 fPos;

uniform vec3  cameraPos;
uniform samplerCube cubeSampler;
in vec3 fNormal;
in  vec3 fLightDir;
uniform vec3 lightIntensity;
vec3 phoneColor( vec3 diff,vec3 norm)
{
    vec3 n = normalize(fNormal);
    vec3 light = normalize(fLightDir);
    float sDotN = max(dot (light,n),0.0);
    
    return lightIntensity*sDotN*diff;
}
void main(void)
{
    
    vec3 eye = normalize(fPos - cameraPos); // get view vector
    vec3 n =   normalize(fNormal);
    vec3 r =   reflect(eye, n );           //  get reflect vector
    
    r.y = -r.y;
    r.z = -r.z;
    
    vec4 reflectColor = texture(cubeSampler,r.xyz);
    vec3 pColor = phoneColor(reflectColor.xyz,fNormal);
    fragColor = vec4 (pColor,1.0);//reflectColor ;
    fragColor =  mix(fragColor,vec4(0.0, 0.2, 0.13,0.8),0.65);//set water color,0 = skybox color only; 1 = later color
    fragColor.w =0.77;//set the water transparency 
    
}
