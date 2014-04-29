#version 400 
// It was expressed that some drivers required this next line to function properly

in  vec3 fTexCood;
out vec4 FragColor;

uniform samplerCube cubeSampler;
//uniform sampler2D cubeSampler;

void main(void)
{
    FragColor = texture(cubeSampler, fTexCood);

}