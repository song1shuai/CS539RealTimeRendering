#version 400

out vec4 FragColor;
in vec3 fPos;
uniform samplerCube enviSampler;
uniform  vec3  cameraPos;
in vec3 fNormal;
void main(void)
{
   // FragColor = vec4(fPos.x,1.0,.0,1.0);
    vec3 eye = normalize(fPos - cameraPos);
    vec3 n =   normalize(fNormal);
    vec3 r =   reflect(eye, n );
    
//        r.y = -r.y;
//        r.x = -r.x;
    FragColor = texture(enviSampler,r.xyz);
    //FragColor.r =1.0;
}