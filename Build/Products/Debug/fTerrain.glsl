#version 400

out vec4 FragColor;

in  vec3 fLightDir;
in  vec3 fViewDir;
in  vec3 fNormals;
in  vec4 ShadowPos;
in  vec2 fTexCoord;
in  vec3 fPos;
in  vec3 fBinormal;
in  vec3 fTang;



uniform vec3 lightPos;
uniform vec3 lightIntensity;

const float Log2  = 1.442695;
const float FOGDENSITY = 0.005;
const vec3  FOGDCOLOR = vec3(0.5,0.5,0.6);


uniform sampler2D texLow;
uniform sampler2D texMiddle;
uniform sampler2D texHeigh;
uniform sampler2D texDecal;
uniform sampler2D texNormalHeigh;
uniform sampler2D texNormalMiddle;
uniform sampler2D texNormalLow;

uniform sampler2DShadow ShadowMap;
in float slope;
uniform float maxHight;
vec3 computeNormal(vec3 texel)
{
    vec3 normt = normalize(texel * 2.0 - 1.0);
    mat3 toObjectLocal = mat3(normalize(fTang), normalize(fBinormal), normalize(fNormals));
    
    return normalize(toObjectLocal * normt);
}

vec3 phoneColor( vec3 diff,vec3 norm)
{
    vec3 n = normalize(norm);
    
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
        ShadowCoord.z+=0.005;
      //  float  sum = 0.0;
        shadow =  textureProj(ShadowMap,ShadowCoord);
    }
    return shadow;
    
}
vec3 applyShadow(vec3 phone)
{
    
    float shadowFactor = ComputShadow();
    vec3  finalColor =mix(phone ,phone*shadowFactor,0.9);;
    
    // Gamma correct
    finalColor = pow( finalColor, vec3(1.0 / 2.2) );
    return finalColor;
}

void main(void)
{


   float range;
   vec2  tex = fPos.xz /(15);
   range = 15/4;
   vec4 texd;
   vec4 texn;
   
  if (fPos.y<range)
   {
     texd = texture(texLow,tex);
     texn = texture(texNormalLow,tex);
   }
   else if(fPos.y<2*range)
   {
        texd = mix( texture(texLow,tex),texture(texMiddle,tex),(fPos.y-range)/range );
        texn = mix( texture(texNormalLow,tex),texture(texNormalMiddle,tex),(fPos.y-range)/range );
   }
   else if(fPos.y<3*range)
   {
        texd = mix( texture(texMiddle,tex),texture(texHeigh,tex),(fPos.y-2*range)/range );
        texn = mix( texture(texNormalMiddle,tex),texture(texNormalHeigh,tex),(fPos.y-range)/range );
   }
    else
   {
       texd = texture(texHeigh,tex);
       texn = texture(texNormalHeigh,tex);
   }
    
    
    
    vec3 pColor = phoneColor(texd.xyz,computeNormal(texn.xyz));
    vec3 pColorAndShadow = applyShadow(pColor);
    vec3 pColorShadowAndFog = applyForg(pColorAndShadow);
     FragColor = vec4( pColorShadowAndFog,1.0);
    
}


