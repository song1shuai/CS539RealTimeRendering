#version 400

layout(location = 0) in  vec3 vPos;
layout(location = 1) in  vec2 vTexCoord;


const float velocity = 0.2;
const float amp = 2.0;
const float waveNumber = 0.5;

uniform float dt;
uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 nv;
uniform vec3 lightPos;

out vec4 PosInEye;
out vec3 NormalsInEye;
out vec3 LightInEye;
out vec3 fNormal;
out vec3 fPos;
out vec3 fLightDir;
const float waveAttributes = 5.0;

uniform vec4 wavaParam[4];
const float PI = 3.14159;
const int NUM_WAVES = 4;
uniform vec2 directions[NUM_WAVES];


vec4 computePos(vec3 pos)
{
    vec4 tmpPos =  vec4(pos,1.0);
    
    for (int i = 0; i < 4; i++)
	{
        
        vec2 direction = normalize(directions[i]);
		float speed = wavaParam[i].x;
		float amplitude = wavaParam[i].y;
		float wavelength = wavaParam[i].z;
		float steepness = wavaParam[i].w;
        
		float frequency = sqrt(9.81*2.0*3.1415926/wavelength);
		float phase = speed*frequency;
		float alpha = frequency*dot(direction, tmpPos.xz)+phase*dt;
        
		tmpPos.x += steepness*amplitude*direction.x*cos(alpha);
		tmpPos.y += amplitude*sin(alpha);
		tmpPos.z += steepness*amplitude*direction.y*cos(alpha);
        
	}
    
    return tmpPos;
}

vec3 computeNormal(vec4 pos)
{
    vec3 tmpNormal;
    tmpNormal.x = 0.0;
    tmpNormal.y = 0.0;
    tmpNormal.z = 0.0;
    
    for (int i = 0; i < 4; i++)
	{
		vec2 direction = normalize(directions[i]);
		float speed = wavaParam[i].x;
		float amplitude = wavaParam[i].y;
		float wavelength = wavaParam[i].z;
		float steepness = wavaParam[i].w;
		float frequency = sqrt(waveAttributes/wavelength);
		float phase = speed*frequency;
		float alpha = frequency * dot(direction, pos.xz) + phase*dt;
        
		tmpNormal.x += direction.x * wavelength * amplitude * cos(alpha);
		tmpNormal.y += steepness * wavelength * amplitude * sin(alpha);
		tmpNormal.z += direction.y * wavelength * amplitude * cos(alpha);
    }
    
    return tmpNormal;
    
}


void main(void)
{
    
    vec4 wavePos = computePos(vPos);
    
    vec3 vNormal = computeNormal(wavePos);



   
    fNormal.x = -vNormal.x;
    fNormal.y = 1 - vNormal.y;
    fNormal.z = -vNormal.z;
    fLightDir = lightPos;
    fPos = wavePos.xyz;
    gl_Position=mvp*wavePos;
    
}
