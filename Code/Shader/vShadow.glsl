#version 400

layout(location = 0) in  vec3 vPos;
layout(location = 1) in  vec2 vTexCoord;
uniform mat4 mvp;
out vec2 fTexCood;
void main(void)
{
    fTexCood=vTexCoord;
    gl_Position=mvp*vec4(vPos,1.0);
    
}
