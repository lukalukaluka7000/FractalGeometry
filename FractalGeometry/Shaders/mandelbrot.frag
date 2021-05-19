#version 330
uniform float SW;
uniform float SH;
uniform int limit;
uniform vec2 uvMin;
uniform vec2 uvMax;
out vec4 outColor;

void main(){
    float fragmentX = gl_FragCoord.x;
    float fragmentY = gl_FragCoord.y;
    
    vec2 c; 
    //c.x=((pixel.x-xmin)/ float(SW-xmin))*(uvMax.x-uvMin.x)+uvMin.x;
    //c.y=((pixel.y-ymin)/ float(SH-ymin))*(uvMax.y-uvMin.y)+uvMin.y;
    c.x = ((uvMax.x - uvMin.x)/SW) * fragmentX + uvMin.x;
    c.y = ((uvMax.y - uvMin.y)/SH) * fragmentY + uvMin.y;
    
    vec2 complex_curr= vec2(0.0f, 0.0f);
    vec2 complex_next= vec2(0.0f, 0.0f);
    
    bool isDone = false; 
    int divStep = 0;
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


    outColor = vec4(float(divStep)/12.0f, float(divStep)/20.0f, float(divStep)/8.0f, 1.0f);
    //outColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
        
}