#version 400

layout(location = 0) in  vec3 vPos;
layout(location = 1) in  vec3 vNormals;
layout(location = 2) in  vec2 vTexCoord;
layout(location = 3) in  vec3 vTangent;



uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 nv;
uniform mat4 view;
uniform vec3 lightPos;


out vec2 fTexCood;
out vec3 fNormals;

out vec3 lightDir;
out vec3 viewDir;
out vec3 fPos;

void main(void)
{
    
    //pass along the texcood to fragment shader
     fTexCood=vTexCoord;
     fNormals = nv*vNormals;
     vec3 posInEye = nv * vPos;
     lightDir = normalize(lightPos-posInEye);
     viewDir  = normalize(-posInEye);
    fPos = vPos;
    fNormals = vNormals;
    
     gl_Position=mvp*vec4(vPos,1.0);
    
}
