#version 330
uniform float SW;
uniform float SH;
uniform int limit;
uniform vec2 uvMin;
uniform vec2 uvMax;

in vec2 pixel;
vec2 ndc;
//out vec2 c;
flat out int divStep;
float xmin = 0.0f;
float ymin = 0.0f;
void main(){
    ndc.x = (2*pixel.x)/SW - 1;
    ndc.y = 1 - (2*pixel.y)/SH;
    gl_Position = vec4(ndc, 0.0f, 1.0f);
    vec2 c;
    c.x=((pixel.x-xmin)/ float(SW-xmin))*(uvMax.x-uvMin.x)+uvMin.x;
    c.y=((pixel.y-ymin)/ float(SH-ymin))*(uvMax.y-uvMin.y)+uvMin.y;
    
    
    
    vec2 complex_curr= vec2(0.0f, 0.0f);
    vec2 complex_next= vec2(0.0f, 0.0f);
    
    bool isDone = false; divStep = 0;
    while(!isDone && divStep != limit) {
        complex_next = vec2(0.0f, 0.0f);
        complex_next.x = pow(complex_curr.x,2)-pow(complex_curr.y,2)+c.x;
        complex_next.y = 2*complex_curr.x*complex_curr.y+c.y;
        float modulComplexNext=sqrt(pow(complex_next.x, 2) + pow(complex_next.y, 2));
        if(modulComplexNext > 2){
            isDone=true;
            break;
        }
        else{
            complex_curr = complex_next;
        }
        divStep+=1;
    }
    if(!isDone)
        divStep = 0;
    // if(divStep > 0 && divStep < 3)
        // divStep = 0;
    
}