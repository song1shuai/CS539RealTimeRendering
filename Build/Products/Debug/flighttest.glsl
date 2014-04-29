#version 400

out vec4 FragColor;

in  vec3 fLightDir;
in  vec3 fViewDir;
in  vec3 fNormals;
in  vec4 ShadowPos;
in  vec2 fTexCoord;



uniform vec3 lightPos;
uniform vec3 lightIntensity;

const float Log2  = 1.442695;
const float FOGDENSITY = 0.05;
const vec3  FOGDCOLOR = vec3(0.4,0.4,0.4)*0.65;


uniform sampler2D texDiffuse;
uniform sampler2D texAlpha;
uniform sampler2D texSpecular;
uniform sampler2D texNormal;
uniform sampler2D texDecal;
uniform sampler2DShadow ShadowMap;


vec3 phoneColor( vec3 diff,vec3 norm)
{
    vec3 n = normalize(fNormals);
    
    float sDotN = max(dot (fLightDir,n),0.0);
    
    return lightIntensity*sDotN*diff;
}

vec3 applyForg(vec3 resultColor)
{
    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fogFactor = exp2( -FOGDENSITY *
                            FOGDENSITY *
                            z *
                            z *
                            Log2 );
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    return mix(FOGDCOLOR, resultColor, fogFactor);
    
}

float ComputShadow()
{
    float shadow =0.0;
    if(ShadowPos.w >1.0 )
    {
    
    vec4   ShadowCoord = ShadowPos;
           ShadowCoord.z+=1.1;
    float  sum = 0.0;
    shadow =  textureProj(ShadowMap,ShadowCoord);
    }
    return shadow;
    
}
vec3 applyShadow(vec3 phone)
{
    
    float shadowFactor = ComputShadow();
    vec3  finalColor =mix(phone ,phone*shadowFactor,0.8);;
    
    // Gamma correct
    finalColor = pow( finalColor, vec3(1.0 / 2.2) );
    return finalColor;
}


void main(void)
{
    
    
    vec4 texd = texture(texDiffuse,fTexCoord);
    vec3 pColor = phoneColor(texd.xyz,fNormals);
    vec3 pColorAndShadow = applyShadow(pColor);
    vec3 pColorShadowAndFog = applyForg(pColorAndShadow);
    
    FragColor =vec4(pColorShadowAndFog,1.0);
    
    
    //FragColor = vec4(ApplyForg(LightAndShadow(texd.xyz)),1.0);
   
    //FragColor = vec4(fNormals.y,0.0,0.0,1.0);
    //FragColor = vec4 (LightAndShadow(texd.xyz),1.0);
    //FragColor = texd;
    
}
