#version 400
out vec4 FragColor;
in  vec3 PosInWorld;
in  vec3 fNormals;
in  vec3 lightIneye;
in  vec4 PosInEye;
in  vec4 ShadowPos;
in  vec2 fTexCoord;


in  vec3 fLightDir;
in  vec3 fViewDir;

uniform vec3 lightPos;
uniform vec3 lightIntensity;

const float Log2  = 1.442695;
const float FOGDENSITY = 0.005;
const vec3  FOGDCOLOR = vec3(0.4,0.4,0.4)*0.65;



const float k0 = 1.0;                   //constant attenuation
const float k1 = 0.0;                   //linear attenuation
const float k2 = 0.0;                   //quadratic attenuation


uniform sampler2D texDiffuse;
uniform sampler2D texNormal;
uniform sampler2DShadow ShadowMap;


vec3 ApplyForg(vec3 resultColor)
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

vec3 phoneColor( vec3 diff,vec3 norm)
{
    
    

    
    //vec3  r = reflect (-fLightDir , norm);
    float sDotN = max(dot (fLightDir,norm),0.0);
    
    return diff*lightIntensity*sDotN;
}


float ComputShadow()
{
    float shadow =0.0;
    
    if(ShadowPos.w <= 0.0) return 1.0f;
    
    vec4   ShadowCoord = ShadowPos;
           ShadowCoord.z+=0.1;//
 
        
    if(ShadowPos.w >1.0 )
    {
        
   
        //float sum = 0.0;
        
           // sum += textureProjOffset(ShadowMap, ShadowPos, ivec2(-2,-2));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-1,-2 ));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 1,-2));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 2,-2));
        //
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-2,-1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-1,-1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 1,-1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 2,-1));
        //
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-2, 1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-1, 1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 1, 1));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 2, 1));
        //
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-2, 2));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2(-1, 2));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 1, 2));
        //    sum += textureProjOffset(ShadowMap, ShadowCoord, ivec2( 2, 2));
        //    
        //    shadow = sum/16.0;
        
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

//    vec4 texColor = texture( texDiffuse, fTexCood );
void main(void)
{
    
    
     vec4 texNorm =  texture( texNormal, fTexCoord );
     vec4 texColor = texture( texDiffuse, fTexCoord);
    
    
    //FragColor = vec4 (LightAndShadow(texColor.xyz,texNorm.xyz),1.0);
    
    //FragColor = vec4 (LightAndShadow(vec3(1.0,1.0,1.0),texNorm.xyz),1.0);
   // FragColor =texColor;
    
    vec3 pColor = phoneColor(texColor.xyz,texNorm.xyz);
    vec3 pColorAndShadow = applyShadow(pColor);
    vec3 pColorShadowAndFog = ApplyForg(pColorAndShadow);
    
    FragColor =vec4(pColorShadowAndFog,1.0);
   // FragColor = vec4(1.0 ,0.0,0.0,1.0);
    
}


