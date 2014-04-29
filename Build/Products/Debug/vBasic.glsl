#version 400

layout(location = 0) in  vec3 vPos;
//layout(location = 1) in  vec3 vNormals;
//layout(location = 2) in  vec2 vTexCoord;

uniform mat4 mvp;

void main(void)
{

    gl_Position=mvp*vec4(vPos,1.0);


    
    
}
