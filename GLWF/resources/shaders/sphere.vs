#version 330
uniform float pointScale;
uniform float pointRadius;
uniform mat4 MVP;
uniform mat4 MV;
in vec3 vp;
in vec3 col;
out vec3 fcol;
void main() 
{
  vec3 posEye = vec3(MVP*vec4(vp,1));
  float dist = length(posEye);
  gl_PointSize = 0.09 * (pointScale/dist);
  gl_Position = MVP*vec4(vp, 1.0);
  fcol = col;
}