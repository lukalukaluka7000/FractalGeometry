#version 330
uniform float SW;
uniform float SH;
uniform int limit;
out vec4 outColor;
in vec2 c;
void main(){
    vec2 complex_curr= vec2(0.0f, 0.0f);
    vec2 complex_next= vec2(0.0f, 0.0f);
    
    int divStep=0;
    bool isDone = false;
    while(!isDone) {
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
        divStep++;
    }
    if(isDone){
        outColor = vec4(divStep/limit, divStep/limit/2.0f, divStep/limit/3.0f, 1.0f);
    }
    else{
        outColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }    
}