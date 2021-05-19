#version 330
uniform float SW;
uniform float SH;

in vec2 screenCoords;

vec2 ndc;

void main(){
    ndc.x = (2*screenCoords.x / SW) - 1;
    ndc.y = 1 - ( 2 * screenCoords.y ) / SH;
    gl_Position = vec4(ndc.x, ndc.y, 0.0f, 1.0f);
}