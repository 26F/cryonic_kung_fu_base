
#version 430 core

#define PI 3.141592

uniform vec2 iResolution;
uniform float iTime;
uniform vec4 iMouse;
uniform int  iKeyboard;

vec2 u = gl_FragCoord.xy;
out vec4 c_out;


float line_segment(in vec2 p, in vec2 a, in vec2 b) {
    vec2 ba = b - a;
    vec2 pa = p - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.);
    return length(pa - h * ba);
}


void main()
{
    
    
    vec2 rr = iResolution.xy, uv = (u + u - rr) / rr.y;
    vec2 m = iMouse.xy;
    m = (m + m - rr) / rr.y;
    m.y *= -1.0;
    m = normalize(m);
    m *= 3.0;
    float f = 0.01 / line_segment(uv, vec2(0.0, 0.0), m);
    vec3 cl = vec3(f) * vec3(4.0, 1.0, 0.5);
    c_out = vec4(cl, 1.0);
    
    
}