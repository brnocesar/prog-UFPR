#include <stdio.h>
#include <math.h>

void main() {
    double dt, t,
        x=0, vx=0, ax=0,
        y=0, vy=0, ay=-10.0,
        v=100, teta=45, rad=M_PI/180.0;

    vx = v*cos(teta*rad);
    vy = v*sin(teta*rad);
    
    dt = 0.0001;
    for (t=0; t<=100; t=t+dt) {

        printf("%g %g %g %g %g\n", t, x, y, vx, vy);

        if(y<0) break; //projetil chega ao nivel 0, para de calcular
        
        x  =  x + vx * dt;
        y  =  y + vy * dt;
        vx = vx + ax * dt;
        vy = vy + ay * dt;
    }
}
