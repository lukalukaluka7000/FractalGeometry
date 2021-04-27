#version 330
uniform float SW;
uniform float SH;
uniform int limit;
uniform vec2 uvMin;
uniform vec2 uvMax;

in vec2 pixel;
vec2 ndc;
out vec2 c;
float xmin = 0.0f;
float ymin = 0.0f;
void main(){
    ndc.x = (2*pixel.x)/SW - 1;
    ndc.y = 1 - (2*pixel.y)/SH;
    gl_Position = vec4(ndc, 0.0f, 1.0f);
    
    c.x=((pixel.x-xmin)/ float(SW-xmin))*(uvMax.x-uvMin.x)+uvMin.x;
    c.y=((pixel.y-ymin)/ float(SH-ymin))*(uvMax.y-uvMin.y)+uvMin.y;
}