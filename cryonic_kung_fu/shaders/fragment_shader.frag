
#version 430 core

#define PI 3.141592

uniform vec2 iResolution;
uniform float iTime;
uniform vec4 iMouse;
uniform int  iKeyboard;

vec2 u = gl_FragCoord.xy;
out vec4 c_out;

mat2 rot2(float a)
{

    
    float s = sin(a);
    float c = cos(a);
    
    return mat2(c, -s, s, c);

}



float wstar(vec2 uv, float i)
{

    uv *= rot2(i);
    uv *= 13.0;
    
    float f = (0.1 / length(uv.x * uv.y * 100.0)) * (1.0 - length(uv));
    vec2 uvd = uv * rot2(45.0 * (PI / 180.0));
    f += (0.5 / length(uvd.x * uvd.y * 100.0)) * (1.0 - length(uvd) * 1.86);
    f += 0.1 / (length(uv) - 0.01);
    return f;
}


void main()
{
    vec2 rr = iResolution.xy, uv = (u + u - rr) / rr.y;
    
    uv.x += sin(uv.y + iTime) * 0.1;

    vec3 color = vec3(0.0);

    for (float i = 0.0; i < 19.0; i++)
    {
    
        
        
        color.r += wstar(uv + vec2(cos(i + iTime), sin(i + iTime)) * i * 0.05, i * 2.0);
        color.g += wstar(uv + vec2(cos(i + iTime), sin(i + iTime)) * i * 0.05, i * 2.0);
        color.b += wstar(uv + vec2(cos(i + iTime), sin(i + iTime)) * i * 0.05, i * 2.0);
    
    }

    c_out = vec4(color, 1.0);
}