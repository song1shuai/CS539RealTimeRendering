#version 400

layout(location = 0) out  float FragColor;
in vec2 fTexCood;
uniform sampler2D texAlpha;
uniform bool hasAlpha;

void main(void)
{
    if (hasAlpha)
    {
         vec4 texa = texture(texAlpha,fTexCood);
        if (texa.r <0.1)
        {
            discard;
        }
    }
    
    FragColor = gl_FragCoord.z ;
}
