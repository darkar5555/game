#version 330
const float PI = 3.1415926535897932384626433832795;
out vec4 frag_colour;
in vec3 fcol;
void main() 
{
    if(dot(gl_PointCoord-0.5,gl_PointCoord-0.5)>0.25)
        discard;
    else
    {
        vec3 lightDir = vec3(0.3,0.3,0.9);
        vec3 N;
        N.xy = gl_PointCoord* 2.0 - vec2(1.0);
        float mag = dot(N.xy, N.xy);
        N.z = sqrt(1.0-mag);
        float diffuse = max(0.0, dot(lightDir, N));
        frag_colour = vec4(fcol, 1.0)*diffuse;
    }
}