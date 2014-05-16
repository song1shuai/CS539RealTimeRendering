#version 400

layout(location = 0) in  vec3 vPos;
layout(location = 1) in  vec3 vNormals;
layout(location = 2) in  vec2 vTexCoord;


out vec3 fTexCood;
uniform mat4 mvp;

void main(void)
{

    vec4 pvm_pos=mvp*vec4(vPos,1.0);
    gl_Position=pvm_pos.xyww;
    fTexCood=vPos;
    
    
}
