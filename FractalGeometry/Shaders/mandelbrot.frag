#version 330
uniform float SW;
uniform float SH;
uniform int limit;
out vec4 outColor;
//in vec2 c;
flat in int divStep;
void main(){
    outColor = vec4(float(divStep)/limit, float(divStep)/limit/2, float(divStep)/limit/3, 1.0f);
    //outColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
        
}